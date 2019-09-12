char A;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
  A = Serial.read();
  }
  if(A=='N'){
    Serial.println("Teeruch Sintusiri");
  }
  else if(A=='S'){
    Serial.println("Physics");
  }
  else if(A=='G'){
    Serial.println("3.55");
  }
}
