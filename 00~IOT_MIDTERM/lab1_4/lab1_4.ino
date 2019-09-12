int n;
int i;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    n=Serial.parseInt();
  }
  if(n>=3 && n<=6){
      
  for(i=0;i<=n;i++){
    digitalWrite(LED_BUILTIN, HIGH);  delay(500);
    digitalWrite(LED_BUILTIN, LOW);   delay(500); 
    }
}
}
