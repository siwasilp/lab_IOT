#include <SimpleDHT.h>
#include "LedControl.h"
LedControl lc=LedControl(5,18,19,1);
unsigned long delaytime=250;
int pinDHT22 = 4;
SimpleDHT22 dht22;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop() {
  Serial.println("=================================");
  Serial.println("Sample DHT22...");
  
  
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.print((float)humidity); Serial.println(" RH%");
  
  float t= temperature;
  int c3 = (t-int(t))/0.1;
  int c2 = int(t)%10;t=t/10;
  int c1 = int(t)%10;
  Serial.println(temperature);
  Serial.println(c1);
  Serial.println(c2);
  Serial.println(c3);
  lc.setDigit(0,7,c1,false);
  lc.setDigit(0,6,c2,true);
  lc.setDigit(0,5,c3,false);
  lc.setChar(0, 4,'c',false);
  float h= humidity;
  int h3 = (h-int(h))/0.1;
  int h2 = int(h)%10;h=h/10;
  int h1 = int(h)%10;
  Serial.println(humidity);
  Serial.println(h1);
  Serial.println(h2);
  Serial.println(h3);
  lc.setDigit(0,3,h1,false);
  lc.setDigit(0,2,h2,true);
  lc.setDigit(0,1,h3,false);
  lc.setChar(0, 0,'H',false);

}
