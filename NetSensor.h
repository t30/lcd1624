/*! @file NetSensor.h
 @author Ing. M.Lampugnani
 @par Company:
 MyCompany
 @version 0.0.2-scrolling branch
 @date 10th march 2011 */
void requestTemp(){
  prntDBG(4,"Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  prntDBG(4,"DONE");
}

float readTemp(int sensNr){
  float Temperature = sensors.getTempCByIndex(sensNr);
  return Temperature;
}



