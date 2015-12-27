/*
 * Android ADK(AOA1.0) implementation for GR-SAKURA
 * Copyright (C) 2012 Yuuichi Akagawa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <rxduino.h>
#include "tkusbhost.h"
#include "AndroidAccessory.h"

//Android ADK specified(AOA1.0)
#define USB_ACCESSORY_VENDOR_ID         0x18D1
#define USB_ACCESSORY_PRODUCT_ID        0x2D00
#define USB_ACCESSORY_ADB_PRODUCT_ID    0x2D01

#define ACCESSORY_STRING_MANUFACTURER   0
#define ACCESSORY_STRING_DESCRIPTION    2
#define ACCESSORY_STRING_VERSION        3
#define ACCESSORY_STRING_URI            4
#define ACCESSORY_STRING_SERIAL         5

#define ACCESSORY_GET_PROTOCOL          51
#define ACCESSORY_SEND_STRING           52
#define ACCESSORY_START                 53

#define DEBUG

/***********************************************************************************/
// Android ADK implementation
/***********************************************************************************/

AndroidAccessory::AndroidAccessory(const char *manufacturer,
                                   const char *model,
                                   const char *description,
                                   const char *version,
                                   const char *uri,
                                   const char *serial) : manufacturer(manufacturer),
                                                         model(model),
                                                         description(description),
                                                         version(version),
                                                         uri(uri),
                                                         serial(serial),
                                                         connected(false)
{
    if(tkusbh_init() != TKUSBH_OK)
    {
#ifdef DEBUG
        Serial.print("!!! USB Host Initialization ERROR !!! system halt\n");
#endif
        while(1);
    }
}

void AndroidAccessory::powerOn(void) //Empty. To ensure compatibility
{
}

bool AndroidAccessory::isAccessoryDevice()
{
    if(USBHostInfo.DeviceDesc.idVendor == USB_ACCESSORY_VENDOR_ID &&
        (USBHostInfo.DeviceDesc.idProduct == USB_ACCESSORY_PRODUCT_ID ||
         USBHostInfo.DeviceDesc.idProduct == USB_ACCESSORY_ADB_PRODUCT_ID)
    ){
        return true;
    }else{
        return false;
    }    
}

unsigned short AndroidAccessory::getProtocol()
{
    unsigned short protocol;
    unsigned short req = (USB_DIR_D2H|USB_REQ_TYPE_VENDOR|USB_REQ_RECIPIENT_DEVICE) | (ACCESSORY_GET_PROTOCOL << 8);
    if(tkusbh_control_msg(req, 0, 0, 2, (unsigned char*)&protocol, 1000) < 0 ){
        return -1;
    }else{
        return protocol;
    }
}

int AndroidAccessory::sendString(unsigned short index, const char* buff)
{
    unsigned short len = strlen(buff) + 1;
#ifdef DEBUG
    printf("sendString: %s\n", buff);
#endif
    unsigned short req = (USB_DIR_H2D|USB_REQ_TYPE_VENDOR|USB_REQ_RECIPIENT_DEVICE) | (ACCESSORY_SEND_STRING << 8);
    return tkusbh_control_msg(req, 0, index, len, (unsigned char *)buff, 1000);
}

int AndroidAccessory::switchDevice()
{
    unsigned char *dummy;
    unsigned short req = (USB_DIR_H2D|USB_REQ_TYPE_VENDOR|USB_REQ_RECIPIENT_DEVICE) | (ACCESSORY_START << 8);
    return tkusbh_control_msg(req, 0, 0, 0, dummy, 1000);
}

#define ACCESSORY_STRING_MODEL          1

bool AndroidAccessory::findEndpoints(void)
{
    char buf[128];
    int i = 0;
    int epcount = 0;

    tkusbh_get_descriptor(CONFIG_DESCRIPTOR_TYPE, 0, buf, 128);

    int len = USBHostInfo.ConfigDesc.wTotalLength;
    while(i < len)
    {
        if(buf[i+1] == ENDPOINT_DESCRIPTOR_TYPE){
            EndpointDesc_t *desc = (EndpointDesc_t *)&buf[i];
            if( desc->bEndpointAddress & 0x80 ){
                inEP  = desc->bEndpointAddress;
            }else{
                outEP = desc->bEndpointAddress;
            }
#ifdef DEBUG
            printf("bEndpointAddress(%d)= %d\n", epcount, desc->bEndpointAddress);
#endif
            epcount++;
            if( epcount >= 2 ){
                i = len;
            }else{
                i += buf[i+0];
            }
        }else{
            i += buf[i+0];
        }
    }
    if( epcount < 2 ){
        return false;
    }else{
        return true;
    }
}

int AndroidAccessory::read(void *buff, int len, int timeout)
{
    return tkusbh_bulk_read(inEP,  (unsigned char *) buff, len, timeout);
}

int AndroidAccessory::write(void *buff, int len, int timeout)
{
    return tkusbh_bulk_write(outEP, (unsigned char *)buff, len, timeout);
}

bool AndroidAccessory::isConnected()
{
    //Check the disconnect state
    if(connected && tkusbh_is_connected() == TKUSBH_DISCONNECT)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
#ifdef DEBUG
        printf("*DisConnected...\n");
#endif
        connected = false;
        return false;
    }
    
    //Already switched    
    if(connected)
        return true;

    //Start Enumeration
    if(tkusbh_connect(500) != TKUSBH_OK)
    {
#ifdef DEBUG
        printf("*Connection TIMEOUT. Retry...\n");
#endif
        return false;
    }

    //Connected
#ifdef DEBUG
    printf("VID=%04x ",  USBHostInfo.DeviceDesc.idVendor);
    printf("PID=%04x\n", USBHostInfo.DeviceDesc.idProduct);
#endif

    //check vaild device
    if(isAccessoryDevice()){//already change Accessory mode
        //find Bulk transfer endpoints (IN/OUT)
        if( !findEndpoints() )
        {
#ifdef DEBUG
            Serial.println("Endpoint not found.");
#endif
            tkusbh_disconnect(TIMEOUT_INFINITE);
            return false;
        }
        connected = true;
        return true;
    }

    //get protocol
    unsigned short protocol = -1;
    protocol = getProtocol();
    if(protocol < 1 ){
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }
#ifdef DEBUG
    printf("ADK supportd.(%d)\n", protocol);
#endif

    //sendString MANUFACTURE
    if(sendString(ACCESSORY_STRING_MANUFACTURER, manufacturer) < 0)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }
    //sendString MODEL
    if(sendString(ACCESSORY_STRING_MODEL, model) < 0)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }
    //sendString DESCRIPTION
    if(sendString(ACCESSORY_STRING_DESCRIPTION, description) < 0)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }
    //sendString VERSION
    if(sendString(ACCESSORY_STRING_VERSION, version) < 0)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }   
    //sendString URI
    if(sendString(ACCESSORY_STRING_URI, uri) < 0)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }   
    //sendString SERIAL
    if(sendString(ACCESSORY_STRING_SERIAL, serial) < 0)
    {
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }

    //Start Accessory mode
#ifdef DEBUG
    printf("Start Accessory mode\n");
#endif
    switchDevice();

    //Disconnect just in case
    tkusbh_disconnect(1000);

    //Will wait a little
    delay(500);

    //Re-Enumeration
    tkusbh_connect(1000);

    //check vaild device
    if(!isAccessoryDevice()){
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }
    
#ifdef DEBUG
    printf("VID=%04x ",  USBHostInfo.DeviceDesc.idVendor);
    printf("PID=%04x\n", USBHostInfo.DeviceDesc.idProduct);
#endif

    //find Bulk transfer endpoints (IN/OUT)
    if( !findEndpoints() )
    {
#ifdef DEBUG
        Serial.println("Endpoint not found.");
#endif
        tkusbh_disconnect(TIMEOUT_INFINITE);
        return false;
    }
    
    //Complete switch in the accessory mode
    connected = true;
    return true;
}


