#include <rxduino.h>
#include "AndroidAccessory.h"
#include "iodefine_gcc63n.h"
#include "intvect63n.h"

#define DEBUG

unsigned char msg[64];
unsigned char oldval = 1;
volatile int hcCount = 0;
unsigned char hcBlink = 0;

//Create Accessory instance
AndroidAccessory acc("Manufacturer", "Modelo", "USB ADK para GR-SAKURA", "1.0",
		"http://www.mipagina.es",
		"1234567");

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

	pinMode(PIN_SW,   INPUT);
	pinMode(PIN_LED0, OUTPUT);
	pinMode(PIN_LED1,OUTPUT);
	pinMode(PIN_LED2,OUTPUT);
	pinMode(PIN_LED3,OUTPUT);

	Serial.begin(38400,SCI_SCI0P2x);
	Serial.println("Initializing...");

	initTMR0();

	digitalWrite(PIN_LED1, 0);
	digitalWrite(PIN_LED3, 0);
}

//**************************************************************************
void loop() {

	if (acc.isConnected() == false) {
		digitalWrite(PIN_LED1, 1);
		delay(100);

		return;
	}

	int len = acc.read(msg, sizeof(msg), 1);
	    if (len > 0) {
	        // assumes only one command per packet
	        if (msg[0] == 0x1) {
	            if( msg[1] == 0x01){
	                digitalWrite(PIN_LED3, HIGH);
	            } else  {
	                digitalWrite(PIN_LED3, LOW);
	            }
	        }
	        if(msg[0] == 0x02) {
	               analogWrite(PIN_LED1, msg[1]);
	        }
	    }

	    //Send data(GR-SAKURA->Android)
	    unsigned char val = digitalRead(PIN_SW);
	    if( val != oldval ){
	        msg[0] = 0x1;
	        if( val == 0 ){
	            msg[1] = 0x1;
	        }else{
	            msg[1] = 0x0;
	        }
	        acc.write(msg, 2, 10);
	        oldval = val;
	    }



}
//******************************************************************************
void Excep_TMR0_OVI0(void) {

	static unsigned char cnt = 0;
	static unsigned char toggle = 0;

	if (++cnt > 12) {

		toggle ^= 1; //aprox 1 seg
		digitalWrite(PIN_LED0, toggle);
		cnt = 0;

	}
}


