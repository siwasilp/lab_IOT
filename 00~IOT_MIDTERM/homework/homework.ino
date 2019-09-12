#include "LedControl.h"
LedControl lc=LedControl(19,5,18,1);
unsigned long delaytime=250;
int i;
int j,ReadByte=0;
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  Serial.begin(9600);
}
void loop() {
    //if(Serial.available()){
      //j=Serial.parseInt();
      //Serial.println(j);
      for(i=6080400;i<=999999999;i--){
        if(i>6080365){
          int x = i;
          lc.setDigit(0,0,x%10,false); x=x/10;
          lc.setDigit(0,1,x%10,false); x=x/10;
          lc.setDigit(0,2,x%10,false); x=x/10;
          lc.setDigit(0,3,x%10,false); x=x/10;
          lc.setDigit(0,4,x%10,false); x=x/10;
          lc.setDigit(0,5,x%10,false); x=x/10;
          lc.setDigit(0,6,x%10,false); x=x/10;
          lc.setDigit(0,7,x,false);
        }
        if(i<=6080365){
          lc.setChar(0,7,'b',false);
          lc.setDigit(0,6,6,false);
          lc.setDigit(0,5,0,false);
          lc.setDigit(0,4,8,false);
          lc.setDigit(0,3,0,false);
          lc.setDigit(0,2,3,false);
          lc.setDigit(0,1,6,false);
          lc.setDigit(0,0,5,false);
        }
        delay(100);
      }
   //}
}
