void requestTemp(){
  prntDBG(9,"Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  prntDBG(9,"DONE");
}

float readTemp(int sensNr){
  float Temperature = sensors.getTempCByIndex(sensNr);
  return Temperature;
}


