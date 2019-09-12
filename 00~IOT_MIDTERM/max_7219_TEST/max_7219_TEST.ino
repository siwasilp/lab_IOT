#include "LedControl.h"
LedControl lc=LedControl(5,18,19,1);

unsigned long delaytime=250;
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}


void loop() {
  for(int i = 0;i<=99999999;i++){
    int x = i;
    lc.setDigit(0,0,x%10,false); x=x/10;
    lc.setDigit(0,1,x%10,false); x=x/10;
    lc.setDigit(0,2,x%10,false); x=x/10;
    lc.setDigit(0,3,x%10,false); x=x/10;
    lc.setDigit(0,4,x%10,false); x=x/10;
    lc.setDigit(0,5,x%10,false); x=x/10;
    lc.setDigit(0,6,x%10,false); x=x/10;
    lc.setDigit(0,7,x%10,false); x=x/10;
    delay(500);
  }
}
