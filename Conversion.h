/*!  thanks to C0t0d0s0 for this function */
byte inttostr(int n, char* s){
  int order=10;
  if(n<order){
    *(s++)=n+'0';
    return 1;
  }
  byte len=2;
  while((len<5)&&(n>=10*order)){
    order*=10;
    len++;
  }
  while(order){
    byte digit=(n/order);
    *(s++)=digit+'0';
    n-=digit*order;
    order/=10;
  }
  return len;
}

