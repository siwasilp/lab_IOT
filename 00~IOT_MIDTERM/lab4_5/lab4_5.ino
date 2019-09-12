#include "DHTesp.h"
#include "LedControl.h"
LedControl lc=LedControl(5,18,19,1);
DHTesp dht;
unsigned long delaytime = +250;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  
  dht.setup(4); 
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity()*10;
  float temperature = dht.getTemperature()*10;
  float t= temperature;
  int c3 = (t-int(t))/0.1;
  int c2 = int(t)%10;t=t/10;
  int c1 = int(t)%10;
  Serial.print(temperature);
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
  Serial.print(humidity);
  Serial.println(h1);
  Serial.println(h2);
  Serial.println(h3);
  lc.setDigit(0,3,h1,false);
  lc.setDigit(0,2,h2,true);
  lc.setDigit(0,1,h3,false);
  lc.setChar(0, 0,'H',false);
}
