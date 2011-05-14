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
void ScrolLine(int line)
{
  static int xL1;
  static int xL2;

  switch(line)
  {
  case 0:
    {
      if( xL1 >= 0 ){
        xL1--;
        prntDBG(10,"if ");
      } 
      else if(xL1 < 0 && abs(xL1) < (ScrolLine1)) {
        xL1--;
        prntDBG(10,"else if ");
      }
      else {
        xL1 = X_MAX;
        updateLine(line, msgSet[MsgRotate[line]]);  
        prntDBG(10,"else ");
        if(MsgRotate[line] > (MESS_NR-2)){
          MsgRotate[line] = 0;
        } 
        else {
          MsgRotate[line]++;
        }

      }

      prntDBG(10,"valore della var x: ");
      prntDBG(10,xL1);
      WrStrLine1(xL1,msgLine1);

      break;
    }
  case 1:
    {

      if( xL2 >= 0 ){
        xL2--;
        prntDBG(10,"if ");
      } 
      else if(xL2 < 0 && abs(xL2) < (ScrolLine2)) {
        xL2--;
        prntDBG(10,"else if ");
      }     
      else {
        xL2 = X_MAX;
        updateLine(line, msgSet[MsgRotate[line]]);  
        prntDBG(10,"else ");
        if(MsgRotate[line] > (MESS_NR-2)){
          MsgRotate[line] = 0;
        } 
        else {
          MsgRotate[line]++;
        }

      }

      prntDBG(10,"valore della var x: ");
      prntDBG(10,xL2);
      WrStrLine2(xL2,msgLine2);
      break;  
    }
  }


}







