#include <TimerOne.h>
#include "Wire.h"
#include "TM1636.h"
#define DEBUG 1
#define KEY_MENU  11
#define KEY_UP    10
#define KEY_DOWN  9
TM1636 tm1636(7,8);

int i=0;
void setup() {
  tm1636.init();
  pinMode(KEY_MENU, INPUT_PULLUP);
  digitalWrite(KEY_MENU, HIGH);
  pinMode(KEY_UP, INPUT_PULLUP);
  digitalWrite(KEY_UP, HIGH);
  pinMode(KEY_DOWN, INPUT_PULLUP);
  digitalWrite(KEY_DOWN, HIGH);
}

void loop() {
   int8_t DispBuff[4];
   if(digitalRead(KEY_MENU) == LOW){
    i=0;
   }
   if(digitalRead(KEY_UP) == LOW){
    i++;
   }
   if(digitalRead(KEY_DOWN) == LOW){
    i--;
   }
  if(i<0){
    i=0;
  }
  if(i>9999){
    i=9999;
  }
  int i0 = i%10;
  int i1 = ((i%100) - i0)/10;
  int i2 = ((i%1000) - i1 -i0)/100;
  int i3 = (i/1000);
  DispBuff[0]=i3;
  DispBuff[1]=i2;
  DispBuff[2]=i1;
  DispBuff[3]=i0;
  tm1636.display(DispBuff);

 
}
