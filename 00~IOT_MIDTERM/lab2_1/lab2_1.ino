#define LED1 18
#define LED2 19
#define LED3 22
#define LED4 23

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}
void loop() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED4, LOW);
  delay(100);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(100);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  delay(100); 
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  delay(100);   
}
