int ReadByte = 0;
void setup() {
      Serial.begin(19200);
      Serial.flush();
      Serial.println("Demo : RS232 Receive & Transmit Data");
      Serial.println("Press Anykey For test...");
      Serial.println(">");
}
void loop() {
  // put your main code here, to run repeatedly:

      if(Serial.available()>0){
        ReadByte = Serial.read();
        Serial.print((char)ReadByte);
        if(ReadByte==0x0D){
          Serial.println();
          Serial.println(">");
        
        }
        }
          
}
