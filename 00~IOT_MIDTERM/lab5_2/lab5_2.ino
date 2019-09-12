#include <TimerOne.h>
#include "Wire.h"
#include "TM1636.h"
#define DEBUG 1
#define KEY_MENU  11
#define KEY_UP    10
#define KEY_DOWN  9
TM1636 tm1636(7,8);

void setup() {
  tm1636.init();
  pinMode(KEY_MENU, INPUT);
  digitalWrite(KEY_MENU, HIGH);
  pinMode(KEY_UP, INPUT);
  digitalWrite(KEY_UP, HIGH);
  pinMode(KEY_DOWN, INPUT);
  digitalWrite(KEY_DOWN, HIGH);
}

void loop() {
   int8_t DispBuff[4];
  if(digitalRead(KEY_MENU) == LOW){
  DispBuff[0]=0;
  DispBuff[1]=0;
  DispBuff[2]=1;
  DispBuff[3]=1;
  tm1636.display(DispBuff);
  }

  if(digitalRead(KEY_UP) == LOW){
  DispBuff[0]=0;
  DispBuff[1]=0;
  DispBuff[2]=1;
  DispBuff[3]=0;
  tm1636.display(DispBuff);
  }

   if(digitalRead(KEY_DOWN) == LOW){
    DispBuff[0]=0;
    DispBuff[1]=0;
    DispBuff[2]=0;
    DispBuff[3]=9;
  tm1636.display(DispBuff);
 }
 
}
