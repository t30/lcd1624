/*! @file Debug.h
  @author Ing. M.Lampugnani
  @par Company:
    MyCompany
  @version 0.0.2-scrolling branch
  @date 10th march 2011 */
  /*!  Definition of debug level */
#define DEBUG  5
unsigned int debugL = DEBUG;
/*!  Write out a debug string over serial port */
void prntDBG(int levelDBG, char* c){

  if(levelDBG <= debugL){    
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

  if(levelDBG <= debugL){    
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





