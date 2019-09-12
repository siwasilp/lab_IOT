float C;
float F;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    Serial.print("input C :");
    C = Serial.parseFloat();
    Serial.println(C);
  F = (9*C/5)+32;
  Serial.print("F = ");
  Serial.println(F);
  }
}
