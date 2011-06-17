/*
 * Copy a character glyph from the myfont data structure to
 * display memory, with its upper left at the given coordinate
 * This is unoptimized and simply uses setPixel() to draw each dot.
 */
void drawChar(uint8_t x, uint8_t y, char c)
{
  uint8_t dots;
  if ((c >= 'A' && c <= 'Z' )||
    (c >= 'a' && c <= 'z') ) {
    c &= 0x1F;   // A-Z maps to 1-26
  } 
  else if (c >= '0' && c <= '9') {
    c = (c - '0') + 27;
  } 
  else if (c == ' ' ) {
    c = 0; // space
  }
  else {
    c = 0; // space
  }
  for (char col=0; col< 6; col++) {
    dots = pgm_read_byte_near(&myfont[c][col]);
    for (char row=0; row < 7; row++) {
      if (dots & (64>>row))   	     // only 7 rows.
        toolbox.setPixel(x+col, y+row, 1);
      else 
        toolbox.setPixel(x+col, y+row, 0);
    }
  }
}


// Write out an entire string (Null terminated)
void drawString(uint8_t x, uint8_t y, char* c)
{
  for(char i=0; i< strlen(c); i++)
  {
    drawChar(x, y, c[i]);
    x+=6; // Width of each glyph
  }
}

// Write out an entire string (Null terminated) - on the first line
void WrStrLine1(uint8_t x, char* c) {
  drawString(x, 0, c);
}

// Write out an entire string (Null terminated) - on the second line
void WrStrLine2(uint8_t x, char* c) {
  drawString(x, 9, c);
}

//// Text bouncing around
//void demoText()
//{
//  prntDBG(7,"Numero di char del messaggio: ");
//  prntDBG(7,sizeof(msg));
//
//  prntDBG(9,"for Cycle executed for: ");
//  prntDBG(9,((sizeof(msg)*6) + X_MAX));
//  int x=X_MAX;
//  //  boolean textDir = false;
//  //boolean textRight = false;
//
//  for (int i=0; i < ((sizeof(msg)*6) + X_MAX); i++) 
//  {
//    x--;
//    //drawString(x,y,msg);
//    WrStrLine1(x,msg);
//    //   drawString(x,y,ftoa(sensors.getTempCByIndex(0)), 5, temp);
//    disp.syncDisplays(); 
//
//    delay(100);
//    disp.clear(); 
//  } 
//}

/*! scoll a string on the MatrixDisplay on a specify line  */
void ScrollingLine(int line)
{
  static int xL[2];
  static int  offsetMsg[2];
  //static int xL2;
  prntDBG(7,"xL: ");
  prntDBG(7,line);

  //!se la stringa (che parte da destra) non ha ancora raggiunto l'estremo sinistro del display
  if( xL[line] >= 0 ){
    prntDBG(8,xL[line]);
    xL[line]--;
    prntDBG(10,"if ");
  } 

  //!se la stringa ha raggiunto l'estremo sinistro del display,
  //quindi parte da un punto di "disegno" virtualmente negativo
  else if(xL[line] < 0 && abs(xL[line]) < 6) {
    prntDBG(8,xL[line]);
    xL[line]--;
    prntDBG(10,"else if ");
  }

  //!se sorpassa un certo limite negativo, oltre ad eseguire le operazioni di routeine
  //possono essere fatte operazioni particoli
  else {
    prntDBG(8,xL[line]);
    //xL[line] = X_MAX;
    //for test
    xL[line] = 0;
    //////////////////////////////////
    //////////////////////////////////
    offsetMsg[line]++;
    //////////////////////////////////
    //////////////////////////////////

    prntDBG(10,"else ");
  }

  unsigned int availLen = (X_MAX+6)-xL[line];
  prntDBG(7,availLen);
  prntDBG(10,"valore della var x: ");
  prntDBG(10,xL[line]);
  //  WrStrLine1(xL[line],msgLine[line]);
  //drawString(xL[line],line*9,msgLine[line]);

  //!scrittura fisica sul display
  int x = xL[line];
//  for(int i=0+offsetMsg[line]; i<=( (X_MAX-xL[line] )/6)+1+offsetMsg[line]; i++)
  for(int i=0+offsetMsg[line]; i<=( (X_MAX-xL[line] )/6)+offsetMsg[line]; i++)
  {
    if(msgLine[line][i] == '\0'){
     break; 
    }
    drawChar(x, line*9, msgLine[line][i]);
    prntDBG(10,msgLine[line][i]);
    x+=6; // Width of each glyph
  }
prntDBG(10,"============");
  //!controlli per rotazione messaggi e fine scroling
  if(offsetMsg[line]>= strlen(msgLine[line])){
    if(MsgRotate[line] > (MESS_NR-2)){
      MsgRotate[line] = 0;
    } 
    else {
      MsgRotate[line]++;
    }
    updateLine(line, msgSet[MsgRotate[line]]);  
    offsetMsg[line] = 0;
    xL[line] = X_MAX;
  }

}
//}


























