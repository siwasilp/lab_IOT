int pushButton = 4;
#define LED1 18
#define LED2 19
#define LED3 22
#define LED4 23
#define BUTTON 4
int i =0;
int count = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT_PULLUP);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);
}


void loop() {
  int buttonState = digitalRead(pushButton);
    if( buttonState==0 ){
     for( i =count ; count <10 ;count ++){
      if(buttonState==0){
      digitalWrite(LED1, HIGH);  digitalWrite(LED2, HIGH); digitalWrite(LED3, HIGH);  digitalWrite(LED4, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);  digitalWrite(LED2, LOW); digitalWrite(LED3, LOW);  digitalWrite(LED4, LOW);
     delay(100);
     Serial.println(i);
     if( digitalRead(pushButton)){
      count = 99;
      }
      }
     }
     digitalWrite(LED1, HIGH);  digitalWrite(LED2, HIGH); digitalWrite(LED3, HIGH);  digitalWrite(LED4, HIGH);
    }
    if( buttonState==1 ){
      digitalWrite(LED1, LOW);  digitalWrite(LED2, LOW); digitalWrite(LED3, LOW);  digitalWrite(LED4, LOW);
       count=0;
      }
    
    
    }
