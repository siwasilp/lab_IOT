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

int i=0;
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
   if(digitalRead(KEY_MENU) == LOW){
    i=1;
   }
   if(digitalRead(KEY_UP) == LOW){
    i=2;
   }
   if(digitalRead(KEY_DOWN) == LOW){
    i=3;
   }
  if(i==1){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);   delay(150);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);   delay(150);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);   delay(150);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);   delay(150);
  }

  if(i==2){
    digitalWrite(LED4, HIGH);
    digitalWrite(LED1, LOW);  delay(150);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);  delay(150);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);  delay(150);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);  delay(150);
  }

   if(i==3){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED4, LOW);  delay(150);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);  delay(150);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, LOW);  delay(150);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED3, LOW);  delay(150);
 }
    
 
}
