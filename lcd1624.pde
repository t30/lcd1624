#include <Messenger.h>
#include <Metro.h>
//#include <stdio.h>
#include "MatrixDisplay.h"
#include "DisplayToolbox.h"
#include "font.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <avr/pgmspace.h>
#include <string.h>
#include "Conversion.h"
#include "Debug.h"

//define for comunication type
#define SERIAL_PORT

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 9


char *msgLine1;
char *msgLine2;
char *msgLine3[2];
//char msg;

//msgLine[0]= msgSet[0];
//msgLine[1]= msgSet[1];

#define MESS_LEN 40 //lunghezza massima dei messaggi
#define MESS_NR  4  //nr massimo di messaggi
char msgSet[MESS_NR][MESS_LEN] = {
  "zero", "uno", "due", "tre"};
//char *msgLine1;
unsigned int FreqLine1 = 1;
unsigned int FreqCount1 = 0;
unsigned int ScrolLine1;
unsigned int FreqLine2 = 3;
unsigned int FreqCount2 = 0;
unsigned int ScrolLine2;
unsigned int MsgRotate[2] = {
  0,0};

// Macro to make it the initDisplay function a little easier to understand
#define setMaster(dispNum, CSPin) initDisplay(dispNum,CSPin,true)
#define setSlave(dispNum, CSPin) initDisplay(dispNum,CSPin,false)

// 4 = Number of displays
// Data = 10
// WR == 11
// True. Do you want a shadow buffer? (A scratch pad)

// Init MatrixDisplay
MatrixDisplay disp(1,7,8, true);
// Pass a copy of the display into the toolbox
DisplayToolbox toolbox(&disp);

Messenger message = Messenger(); 

// Prepare boundaries MAtrixDisplay
uint8_t X_MAX = 0;
uint8_t Y_MAX = 0;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

#include "NetSensor.h"

//Setting up execution frequency f[kHz]= 1/period[msec]
unsigned int period = 50;
Metro Period = Metro(period); 

//Setting up execution frequency f[kHz]= 1/period[msec]
unsigned int periodUpdate = 30000;
Metro Update = Metro(periodUpdate); 

#include "Communication.h"
#include "DrawFunc.h"


void setup() {
  // start serial port
  Serial.begin(115200);
  prntDBG(0,"Booting up...");

  // free(msgLine1);
  // msgLine1 = msgSet[0];
  // updateLine(0, msgSet[0]);
  updateLine(0, msgSet[0]);  
  updateLine(1, msgSet[1]);
  prntDBG(9,"==Print msgSet: ");
  prntDBG(9,msgSet[0]);
  prntDBG(9,msgSet[1]);
  prntDBG(9,"==Print msgLine 1 e 2: ");
  prntDBG(9,msgLine1);
  prntDBG(9,msgLine2);

  // Fetch bounds (dynamically work out how large this display is) MatrixDisplay
  X_MAX = disp.getDisplayCount() * disp.getDisplayWidth();
  Y_MAX = disp.getDisplayHeight();

  // Prepare MatrixDisplay
  disp.setMaster(0,16);
  //    disp.setSlave(1,15);
  //    disp.setSlave(2,17);
  //    disp.setSlave(3,14);

  // Start up the library for sensor temperature
  sensors.begin();

  // Start up the library for serial messages
  message.attach(messageReady);

  prntDBG(0,"Ing. M.Lampugnani - free for non commercial use");
  prntDBG(0,"System Ready");

  //  updateMsg(0);
  //  updateMsg(1);
}

void loop() {

  /*! Check if there is some data available on serial port  */
  while ( Serial.available() )  
  {
    message.process( Serial.read () );
  } 

  //If the timeout is reached
  // check if need to run ScrlLine function
  if (Period.check() == 1)
  {
    Period.reset();

    if(msgLine1 && FreqCount1 < FreqLine1){
      //ScrolLine(1);
      FreqCount1++;
    } 
    else {
      FreqCount1 = 0;
      ScrolLine(0);
    }

    if(msgLine2 && FreqCount2 < FreqLine2){
      //ScrolLine(2);
      FreqCount2++;
    } 
    else {
      FreqCount2 = 0;
      ScrolLine(1);
    }

    disp.syncDisplays(); 

    //da vedere
    //    if(FreqCount1 == 0 && FreqCount2 == 0){
    //      disp.clear(); 
    //    }

  }

  if (Update.check() == 1)
  {
    Update.reset();
//    updateLine(0, msgSet[MsgRotate[0]]);  
//    updateLine(1, msgSet[MsgRotate[1]]);
    //    updateMsg(0);
    //    updateMsg(1);
  }


}




