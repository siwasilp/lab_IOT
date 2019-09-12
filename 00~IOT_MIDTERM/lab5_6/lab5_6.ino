#include <TimerOne.h>
#include "Wire.h"
#include "TM1636.h"
#define DEBUG 1
#define KEY_MENU  11
#define KEY_UP    10
#define KEY_DOWN  9
TM1636 tm1636(7,8);

#define LED4  5
#define LED3  4
#define LED2  3
#define LED1  2

int R=0;
int G=0;
int B=0;
void setup() {
  tm1636.init();
  pinMode(KEY_MENU, INPUT);
  digitalWrite(KEY_MENU, HIGH);
  pinMode(KEY_UP, INPUT);
  digitalWrite(KEY_UP, HIGH);
  pinMode(KEY_DOWN, INPUT);
  digitalWrite(KEY_DOWN, HIGH);
  pinMode(LED1 , OUTPUT);
  pinMode(LED2 , OUTPUT);
  pinMode(LED3 , OUTPUT);
  pinMode(LED4 , OUTPUT);
}

void loop() {
   int8_t DispBuff[4];
   if(digitalRead(KEY_MENU) == LOW){R++;}
   if(digitalRead(KEY_UP) == LOW){G++;}
   if(digitalRead(KEY_DOWN) == LOW){B++;}
  if(R==1){
    digitalWrite(LED4, HIGH);
    digitalWrite(LED3, HIGH);
  }
  if(R>1){
    R=0;
    digitalWrite(LED4, LOW);
    digitalWrite(LED3, LOW);
    }
  if(G==1){digitalWrite(LED2, HIGH);}
  if(G>1){
    G=0;
    digitalWrite(LED2, LOW);
  }
  if(B==1){digitalWrite(LED1, HIGH);}
  if(B>1){
    B=0;
    digitalWrite(LED1, LOW);
  } 
  if(R!=1 && G!=1 && B!=1){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  delay(200);
}
