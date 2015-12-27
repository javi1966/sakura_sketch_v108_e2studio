/*GR-SAKURA Sketch Template Version: V1.08*/
/*GR-SAKURA Sketch Template Version: V1.02*/

#include <rxduino.h>
#include <Ethernet.h>
#include "iodefine_gcc63n.h"
#include "./gr_common/intvect63n.h"

#define _BV(bit) (1 << (bit))

TEthernet Ethernet;

// MAC?????????????
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x02, 0x8C };

byte ip[] = { 192, 168, 1, 78 };
byte gateway[] = { 192, 168, 1, 1 };
byte dns[] = { 80, 58, 61, 250 };

EthernetServer server(80);

double fTemperatura = 21.2;

char buf[100];
char estado[3] = "OK";

#ifdef __cplusplus

extern "C" {

void Excep_TMR0_OVI0(void);

}

#endif

//**************************************************************************
void initTMR0() {

	IEN(TMR0,OVI0)= 1;      //enable INT
	IPR(TMR0,OVI0)= 2;//PRIORIDAD 2
	MSTP(TMR0) = 0;//Activate TMR0 unit
	TMR0.TCCR.BIT.CSS = 1;
	TMR0.TCCR.BIT.CKS = 6;//48/8192Mhz
	TMR0.TCR.BIT.CCLR = 1;//
	//ICU.IR[176].BIT.IR = 0;  //flag a 0
	IR(TMR0,OVI0)= 0;
	TMR0.TCR.BIT.OVIE = 1;
}
//***************************************************************************

void setup() {

	pinMode(PIN_LED0, OUTPUT);

	initTMR0();

	Serial1.begin(38400, SCI_USB0);
	// ??????????????????
	//while (Serial.available() == 0);

	Serial1.println("Initializing...");

	/*
	 if (Serial.available() > 0) {
	 // ?????????
	 char c = Serial.read();
	 }
	 */

	/*

	 // DHCP?????????????
	 if (Ethernet.begin(mac,ip) == 0) {
	 // DHCP???????????
	 Serial.println("Failed get address on DHCP");
	 while(1);
	 }
	 Serial.println("Get IP address from DHCP is success.");
	 // ????????????????????
	 */
	Ethernet.begin(mac, ip, dns, gateway);
	server.begin();
	Serial1.print("Please access by browser at http://");
	Serial1.println(Ethernet.localIP());

}

void loop() {

	EthernetClient client = server.available();

	if (client) {
		Serial1.println("new client");

		boolean currentLineIsBlank = true;
		// ????????????????
		while (client.connected()) {

			// (Rxduino??)Ethernet???????
			Ethernet.processPackets();

			// ?????????????????????
			if (client.available()) {
				// ??????????????
				char c = client.read();
				Serial1.write(c);
				// EOL(\n)????????
				if (c == '\n' && currentLineIsBlank) {
					// http ???????????
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: application/json");
					client.println("Connection: close");
					client.println();
					/*
					 client.println("<!DOCUTYPE HTML>");
					 client.println("<html>");
					 client.println("Hello!");
					 client.println("</html>");

					 */
					sprintf(buf,
							"{\"Temperatura\":{\"Temperatura 1\": %2.1f,\"status\":%s}}",
							fTemperatura, estado);

					Serial1.println(buf);

					//client.print("{\"Temperatura\":{\"Temperatura 1\":");
					//	sprintf(buf,"%2.1f",fTemperatura);
					//	client.print(buf);
					//	client.print(",\"status\":");
					//	client.print(estado);
					//	client.println("}}");

					client.println(buf);

					break;
				}

				// EOL(\n)????????
				if (c == '\n') {
					currentLineIsBlank = true;
				}
				//
				else if (c != '\r') {
					currentLineIsBlank = false;
				}
			}
		}

		delay(1);

		client.stop();
		Serial1.println("client disconnected");

	}
}

//**************************************************************************
void Excep_TMR0_OVI0(void) {

	static unsigned char cnt = 0;
	static unsigned char toggle = 0;

	if (++cnt > 12) {

		toggle ^= 1; //aprox 1 seg
		digitalWrite(PIN_LED0, toggle);
		cnt = 0;
	}
}
