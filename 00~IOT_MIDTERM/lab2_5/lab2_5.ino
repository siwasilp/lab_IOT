float ab = 0;
float area = 0;
void setup() {
Serial.begin(9600);

}

void loop() {
 if(Serial.available()){
  ab = Serial.parseFloat();
  Serial.println(ab);
  area = ab*ab/4;
  Serial.print("area = ");
  Serial.println(area);
 }

}
