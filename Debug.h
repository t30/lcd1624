/*!  Definition of debug level */
#define DEBUG  5

/*!  Write out a debug string over serial port */
void prntDBG(int levelDBG, char* c){
  
  if(levelDBG <= DEBUG){    
    Serial.print(millis());
    Serial.print(" - "); 
    
    if(levelDBG>0){      
      Serial.print("DBG: ");
      Serial.print(levelDBG);
      Serial.print(" msg: ");
    }
    
    Serial.println(c);
  }
  
}

/*!  Write out a debug string over serial port */
void prntDBG(int levelDBG, int c){
  
  if(levelDBG <= DEBUG){    
    Serial.print(millis());
    Serial.print(" - ");
    
    if(levelDBG>0){
      Serial.print("DBG: ");
      Serial.print(levelDBG);
      Serial.print(" msg: ");
    }
    
    Serial.println(c);
  }
  
}




