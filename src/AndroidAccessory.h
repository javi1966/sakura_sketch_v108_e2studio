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
 
#ifndef __ANDROID_ACCESSORY_H
#define __ANDROID_ACCESSORY_H
#include "tkusbhost.h"

#define DEBUG

//bmRequestType
//DIRECTION
#define USB_DIR_H2D 0x00
#define USB_DIR_D2H 0x80
//TYPE
#define USB_REQ_TYPE_STANDARD 0x00
#define USB_REQ_TYPE_CLASS    0x20
#define USB_REQ_TYPE_VENDOR   0x40
//RECIEPIENT
#define USB_REQ_RECIPIENT_DEVICE    0x00
#define USB_REQ_RECIPIENT_INTERFACE 0x01
#define USB_REQ_RECIPIENT_ENDPOINT  0x02
#define USB_REQ_RECIPIENT_OTHER     0x03

class AndroidAccessory {
private:
    const char *manufacturer;
    const char *model;
    const char *description;
    const char *version;
    const char *uri;
    const char *serial;
    bool connected;
    int  inEP;
    int  outEP;

    bool isAccessoryDevice();
    unsigned short getProtocol(void);
    int sendString(unsigned short index, const char* buff);
    int switchDevice(void);
    bool findEndpoints(void);

public:
    AndroidAccessory(const char *manufacturer,
                     const char *model,
                     const char *description,
                     const char *version,
                     const char *uri,
                     const char *serial);
    void powerOn(void);
    bool isConnected(void);
    int read(void *buff, int len, int timeout);
    int write(void *buff, int len, int timeout=TIMEOUT_INFINITE);
};
#endif
