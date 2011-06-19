/*! @file Communication.h
Managing command from communication interface.
  @author Ing. M.Lampugnani
  @par Company:
    MyCompany
  @version 0.0.2-scrolling branch
  @date 10th march 2011 */
  #ifdef SERIAL_PORT
void messageReady() {
  // Loop through all the available elements of the message
  while ( message.available() ) {
    char cmd = message.readChar();
    switch (cmd) {

      //set brightness of display - now only 0 - add a for cycle to extend to all display @todo
    case 'B':
      {
        prntDBG(0,"Set Brightness: ");
        unsigned int brght = message.readInt();
        prntDBG(0,brght);
        disp.setBrightness(0, brght);
        break;
      }

      //cycling around the messages @todo
    case 'C':
      {
        prntDBG(0,"Change message line: "); 
        int lineNr = message.readInt();
        prntDBG(0,lineNr); 

        if(MsgRotate[lineNr] > (MESS_NR-2)){
          MsgRotate[lineNr] = 0;
        } 
        else {
          MsgRotate[lineNr]++;
        }
        prntDBG(0,"Change to msg n: "); 
        prntDBG(0,MsgRotate[lineNr]); 
        break;
      }

      //set brightness of display - now only 0 - add a for cycle to extend to all display @todo
    case 'D':
      {
        prntDBG(0,"Set Debug: ");
        debugL = message.readInt();
        prntDBG(0,debugL);
        break;
      }

      //setta quante volte deve scadere il timer per eseguire l'aggiornamento della riga
      // F line_nr[0-1] value[int]
    case 'F':
      {
        prntDBG(0,"Change conf line: "); 
        int lineNr = message.readInt();
        prntDBG(0,lineNr); 

        prntDBG(0,"Change freq to: "); 
        FreqLine[lineNr] = message.readInt();
        prntDBG(0,FreqLine[lineNr]); 


        break;
      }


    case 'M':
      {
        unsigned int lineNr = message.readInt();
        char *tmpMsg = msgSet[lineNr];
        prntDBG(7,"lunghezza stringa: ");
        prntDBG(7,message.lenString());
        //free(tmpMsg);
        //tmpMsg = msgSet[lineNr];
        //tmpMsg = message.readStr();
        strcpy( tmpMsg, message.readStr());
        prntDBG(5,msgSet[lineNr]);
        break;
      }

    case 'P':
      {
        //change frequency f[khz] = 1 /period[msec]
        prntDBG(0,"Old period: ");
        prntDBG(0,period);
        period = message.readInt();
        Period.interval(period);
        prntDBG(0,"New period: ");
        prntDBG(0,period); 
        //        Serial.println(availableMemory());
        break;
      }

      //shifta il contenuto delbuffer del display
    case 'R':
      {
        prntDBG(8,"ShiftBuffer: "); 
        char dir = message.readChar();

        if(dir == 'L' ){
          prntDBG(8,"shifting LEFT: ");
          disp.shiftLeft();
        } 
        else if(dir == 'R' ){
          prntDBG(8,"shifting RIGHT: "); 
          disp.shiftRight();
        }
        else if(dir == '6' ){
          prntDBG(8,"shifting LEFT 6 pos: "); 
          for(int i = 0; i<6;i++){
            disp.shiftLeft();
          }
        }


        break;
      }

    case 'S':
      {
        prntDBG(5,"StrLenmsgLine1: ");
        prntDBG(5,ScrolLine[0]);
        prntDBG(5,"StrLenmsgLine2: ");
        prntDBG(5,ScrolLine[1]);
        break;
      }

    case 'T':
      {
        unsigned int ore = message.readInt();
        unsigned int minuti = message.readInt();
        if (ore < 24 && minuti < 60){
          //          millistart=(((ore*3600000)+(minuti*60000)) - millis());
          //          prntTime;
          prntDBG(1,"ok");
        } 
        else {
          prntDBG(1,"Err");
        }
        break;
      }

      //setta il periodo per l'aggiornamento dei dati
      //U value[int]
    case 'U':
      {
        //change frequency f[khz] = 1 /period[msec]
        prntDBG(0,"Old periodUpdate: ");
        prntDBG(0,periodUpdate);
        periodUpdate = message.readInt();
        Update.interval(periodUpdate);
        prntDBG(0,"New periodUpdate: ");
        prntDBG(0,periodUpdate); 
        //        Serial.println(availableMemory());
        break;
      }
    default:
      {
        prntDBG(0,"Unknown Command");
      }
    }
  }
}

#endif

void updateLine(unsigned int lineNr, char *str){
  //disp.clear();
  //situation via debug serial print out
  prntDBG(9,"strlen(str)*6 ");
  prntDBG(9,strlen(str)*6);
  //put the message len (in pixel) in a varible used by scoling line function
  ScrolLine[lineNr] = strlen(str)*6+24;
  prntDBG(5,"updateLine ");
  //free(msgLine[lineNr]);

  //adding white space at the begin of msg
  //msgLine[lineNr]= strdup("   ");
  //for (unsigned int n=0; n<=strlen(str); n++){
  //arrange the pointer for this line
  msgLine[lineNr] = str;
  //disp.clear();
  //msgLine[lineNr] = strcat(msgLine[lineNr],str);

}



