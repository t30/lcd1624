//Scroling branch
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

//char *msgLine1;
//char *msgLine2;
char *msgLine[2] = { 
  strdup("Boot"),strdup(" up ")};
//char msg;

//msgLine[0]= msgSet[0];
//msgLine[1]= msgSet[1];

#define MESS_LEN 40 //lunghezza massima dei messaggi
#define MESS_NR  4  //nr massimo di messaggi
char msgSet[MESS_NR][MESS_LEN] = {
  "uno", "2", "3", "4"};
//char *msgLine1;
//variabili legate ai messaggi:
//    - var[0]  ->  riga superiore
//    - var[1]  ->  riga inferiore
//ogni quanti cicli del timer esegue lo scrolling
//la frequenza dipende dalla var::period
unsigned int FreqLine[2] = {
  1,2};
//contatore del numero di cicli eseguiti dal timer
unsigned int FreqCount[2] = {
  0,0};
//lunghezza dei messaggi in scroling ora (in pixel - caratteri*6 (5+spazio))
unsigned int ScrolLine[2] = {
  0,0};
//array in cui viene salvato il nemero del prossimo messaggio in solling
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
  //  updateLine(0, msgSet[0]);  
  //  updateLine(1, msgSet[1]);
  prntDBG(9,"==Print msgSet: ");
  prntDBG(9,msgSet[0]);
  prntDBG(9,msgSet[1]);
  prntDBG(9,"==Print msgLine 1 e 2: ");
  prntDBG(9,msgLine[0]);
  prntDBG(9,msgLine[1]);

  // Fetch bounds (dynamically work out how large this display is) MatrixDisplay
  X_MAX = disp.getDisplayCount() * disp.getDisplayWidth();
  Y_MAX = disp.getDisplayHeight();

  // Prepare MatrixDisplay
  disp.setMaster(0,16);
  //disp.setSlave(1,15);
  //    disp.setSlave(2,17);
  //    disp.setSlave(3,14);

  drawString(0,0,"Testing");
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

    if(msgLine[0] && FreqCount[0] < FreqLine[0]){
      //ScrolLine(1);
      FreqCount[0]++;
    } 
    else {
      FreqCount[0] = 0;
      ScrollingLine(0);
    }

    if(msgLine[1] && FreqCount[1] < FreqLine[1]){
      //ScrolLine(2);
      FreqCount[1]++;
    } 
    else {
      FreqCount[1] = 0;
      ScrollingLine(1);
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








