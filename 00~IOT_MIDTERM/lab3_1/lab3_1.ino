#include <LedControl.h>
LedControl lc=LedControl(19,5,18,1);

unsigned long delaytime=250;

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}


void loop() {
  lc.setChar(0,7,'a',false);
  lc.setDigit(0,6,6,false);
  lc.setDigit(0,5,0,false);
  lc.setDigit(0,4,8,false);
  lc.setDigit(0,3,0,false);
  lc.setDigit(0,2,3,false);
  lc.setDigit(0,1,6,false);
  lc.setDigit(0,0,5,false);
}
