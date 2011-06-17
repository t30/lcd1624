////da mettere in DrawFunc.h
//void setBrightDisp(uint8_t pwmVal){
//  for(uint8_t i=0; i<disp.getDisplayCount(); i++){
//    toolbox.setBrightness(i, pwmVal);
//  }
//}
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
        tmpMsg = msgSet[lineNr];
        //tmpMsg = message.readStr();
        strcpy( tmpMsg, message.readStr());
        prntDBG(5,msgSet[lineNr]);
        //        switch(lineNr){
        //        case 0:
        //          {
        //            //  if(lineNr == 1 )
        //            //  Serial.println("messaggio");
        //            prntDBG(7,"lunghezza stringa: ");
        //            prntDBG(7,message.lenString());
        //            //        Serial.print("contenuto: ");
        //            //        Serial.println(message.readStr());
        //            //msgSet[0]=message.readStr();
        //            free(msgLine1);
        //            //  msg = strdup("  ");
        //            //        msg = strdup("              ");
        //            //        msg = strcat(msg, message.readStr());
        //            //        msg = "               ";
        //            //          msgLine1 = strcat(msgLine1, message.readStr());
        //            strcpy( msgLine1, message.readStr());
        //            ScrolLine1 = strlen(msgLine1)*6;
        //            prntDBG(5,msgSet[0]);
        //            break;
        //          } 
        //        case 1:
        //          {
        //            //else if(lineNr == 2 ) 
        //            //Serial.println("messaggio");
        //            prntDBG(7,"lunghezza stringa: ");
        //            prntDBG(7,message.lenString());
        //            //        Serial.print("contenuto: ");
        //            //        Serial.println(message.readStr());
        //            free(msgLine2);
        //            //msg = strdup("  ");
        //            //        msg = strdup("              ");
        //            //        msg = strcat(msg, message.readStr());
        //            //        msg = "               ";
        //            //          msgLine2 = strcat(msgLine2, message.readStr());
        //            strcpy( msgLine2, message.readStr());
        //            ScrolLine2 = strlen(msgLine2)*6;
        //            //strcpy( msgSet[0], message.readStr());
        //
        //            prntDBG(5,msgLine2);
        //            break;
        //          }
        //        default:
        //          {
        //            //do something 
        //            prntDBG(5,"UnknownPar");
        //            break;
        //          }
        //        }
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

//void updateMsg(char *str, unsigned int msgNr){
//  for(int i=0;i<=strlen(str);i++){
//
//    msgSet[msgNr][i]=str[i];
//  }
//}
//void updateMsg(boolean lineNumb){
//
//  // request temperature data 
//  requestTemp();
//  disp.clear();
//  prntDBG(5,"UpdateMsg Line: ");
//  prntDBG(5,lineNumb);
//  prntDBG(9, "Temperature for the device 1 (index 0) is: ");
//  float tempC = readTemp(0);
//  prntDBG(9, tempC);
//
//  if(lineNumb == 0){
//    free(msgLine1);
//    msgLine1 = strdup("    ");
//
//    inttostr((int)tempC, msgLine1);
//    //msg= "teo";
//
//    prntDBG(8,"Valore temperatura convertito: ");
//    prntDBG(8, msgLine1); 
//  } 
//
//  else if(lineNumb == 1){
//
//    free(msgLine2);
//    msgLine2 = strdup("  ");
//
//    inttostr((int)tempC, msgLine2);
//    //msg= "teo";
//
//    prntDBG(8,"Valore temperatura convertito: ");
//    prntDBG(8, msgLine2); 
//    //ScrolLine2 = strlen(msgLine2)*6;
//  }
//}

void updateLineOLD(unsigned int lineNr, char *str){
  //disp.clear();
  //situation via debug serial print out
  prntDBG(9,"strlen(str)*6 ");
  prntDBG(9,strlen(str)*6);
  //put the message len (in pixel) in a varible used by scoling line function
  ScrolLine[lineNr] = strlen(str)*6;
  prntDBG(8,"updateLine1 ");
  //free(msgLine1);
  //for (unsigned int n=0; n<=strlen(str); n++){
  //arrange the pointer for this line
  msgLine[lineNr] = str;

}

void updateLine(unsigned int lineNr, char *str){
  //disp.clear();
  //situation via debug serial print out
  prntDBG(9,"strlen(str)*6 ");
  prntDBG(9,strlen(str)*6);
  //put the message len (in pixel) in a varible used by scoling line function
  ScrolLine[lineNr] = strlen(str)*6;
  prntDBG(8,"updateLine1 ");
  //free(msgLine[lineNr]);

  //adding white space at the begin of msg
  //msgLine[lineNr]= strdup("   ");
  //for (unsigned int n=0; n<=strlen(str); n++){
  //arrange the pointer for this line
  msgLine[lineNr] = str;
  //    msgLine[lineNr] = strcat(msgLine[lineNr],str);

}










