/*! @file lcd1624.pde
  @author Ing. M.Lampugnani
  @par Company:
    MyCompany
  @version 0.0.2-scrolling branch
  @date 10th march 2011 */
#include <Messenger.h>
#include <Metro.h>
//#include <stdio.h>
#include <MatrixDisplay.h>
#include <DisplayToolbox.h>
#include <font.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <avr/pgmspace.h>
#include "Debug.h"
#include "Conversion.h"
#include <string.h>
//!

//!  Define for comunication type
#define SERIAL_PORT

//!  Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 9

/*!  @name  Set di messaggi in memoria
 //  Settaggio parametri di parcheggio per le stringhe rotanti a display  */
//@{
//! Puntatore ai messaggi da scorrere
char *msgLine[2] = { 
  "    Boot","   up"};
#define MESS_LEN 60 //!<  lunghezza massima dei messaggi
#define MESS_NR  4  //!<  nr massimo di messaggi

//!  Array di messaggi disponibili a display.
/*!  @param  def::MESS_NR    Numero di messaggi
//   @param  def::MESS_LEN   lunghezza massima del messaggio */
char msgSet[MESS_NR][MESS_LEN] = {
  "Scrolling_board",
  "Matteo_lampugnani",
  "Test_scrolling_string",
  "Display_dot_M_16x24_max_4_module"};
//@}

/*!  @name  Scrolling Variables
 Serie di Array contenenti i parametri utilizzati per la rotazione a display
 dei testi presenti in var::msgSet  \n
 //    @param var[0]  ->  riga superiore
 //    @param var[1]  ->  riga inferiore  */
//@{
//!  Ogni quanti cicli del timer esegue lo scrolling
/*!  La frequenza del timer dipende dalla var::period  */
unsigned int FreqLine[2] = {
  1,2};
//!  Contatore del numero di cicli eseguiti dal timer
unsigned int FreqCount[2] = {
  0,0};
//!  Lunghezza dei messaggi in scroling ora (in pixel = caratteri*6 (5+spazio))
unsigned int ScrolLine[2] = {
  0,0};
//!  Array in cui viene salvato il nemero del prossimo messaggio in solling
unsigned int MsgRotate[2] = {
  0,0};
//@}

/*!  @name  Macro LCD define
 Macro to make it the initDisplay function a little easier to understand */
//@{
#define setMaster(dispNum, CSPin) initDisplay(dispNum,CSPin,true)
#define setSlave(dispNum, CSPin) initDisplay(dispNum,CSPin,false)
//@}

// 4 = Number of displays
// Data = 10
// WR == 11
// True. Do you want a shadow buffer? (A scratch pad)

/*!  @name  Diplay variables declaration
 Declaration and variables by modular display
 */
//@{
//!  Init MatrixDisplay
MatrixDisplay disp(1,7,8, true);
//!  Pass a copy of the display into the toolbox
DisplayToolbox toolbox(&disp);

uint8_t X_MAX = 0;//!< Prepare boundaries MAtrixDisplay
uint8_t Y_MAX = 0;//!< Prepare boundaries MAtrixDisplay
//@}

Messenger message = Messenger(); 

/*!  @name  Digital Temperature Sensor (DS18B20)
 Declaration of bus sensor object
 */
//@{
//! Setup a oneWire instance to communicate with any OneWire devices.
/*!  (not just Maxim/Dallas temperature ICs)  
  -  def::ONE_WIRE_BUS  Pin connection for OneWire bus.*/
OneWire oneWire(ONE_WIRE_BUS);
//! Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
//@}

#include "NetSensor.h"

/*!  @name  Task timing function definition
 //  Creazione degli oggetti timer utilizzati per le chiamate ai task  */
//@{
//!Setting up execution frequency f[kHz]= 1/period[msec]
unsigned int period = 50;
//!  Task Veloce.
/*!  Utilizzato per mantenere aggiornate le varibili interne del sistema.  */
Metro Period = Metro(period);
//!Setting up execution frequency f[kHz]= 1/period[msec]
unsigned int periodUpdate = 30000;
//!  Task Lento.
/*!  Utilizzato per mantenere aggiornato lo stato dei sensori e componenti lenti
//   in risposta o nella variazione del loro segnale.  */
Metro Update = Metro(periodUpdate); 
//@}

#include "Communication.h"
#include "DrawFunc.h"


void setup() {
  // start serial port
  Serial.begin(115200);
  prntDBG(0,"Booting up...");

  prntDBG(5,"==Print msgSet: ");
  prntDBG(5,msgSet[0]);
  prntDBG(5,msgSet[1]);
  prntDBG(5,"==Print msgLine 1 e 2: ");
  prntDBG(5,msgLine[0]);
  prntDBG(5,msgLine[1]);

  // Fetch bounds (dynamically work out how large this display is) MatrixDisplay
  X_MAX = disp.getDisplayCount() * disp.getDisplayWidth();
  Y_MAX = disp.getDisplayHeight();

  // Prepare MatrixDisplay
  disp.setMaster(0,16);
  //disp.setSlave(1,15);
  //    disp.setSlave(2,17);
  //    disp.setSlave(3,14);

  // drawString(0,0,"Testing");
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
    //requestTemp();
    //    updateLine(0, msgSet[MsgRotate[0]]);  
    //    updateLine(1, msgSet[MsgRotate[1]]);
    //    updateMsg(0);
    //    updateMsg(1);
  }


}


