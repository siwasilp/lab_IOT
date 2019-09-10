//==== BLYNK : DHT + MAX7219 + LED ========

#define    BLYNK_PRINT Serial
#include   <WiFi.h>
#include   <WiFiClient.h>
#include   <BlynkSimpleEsp32.h>
BlynkTimer timer;

//=========================================

#include   "DHTesp.h"
#include   <DHTesp.h>
#define    Pin_DHT22  15          //pin DHT
DHTesp     dht;

//=========================================

#include  "LedControl.h"
#define   Pin_DIN     2           //pin 2 DIN 
#define   Pin_CS      4           //pin 4 CS
#define   Pin_CLK     5           //pin 5 CLK
LedControl lc = LedControl(Pin_DIN, Pin_CLK, Pin_CS, 1);

//=========================================

char auth[] = "3YLex9xj0s9xdlUSoXCrXxBCoY2Nu5RT";    //Token
char ssid[] = "xxxxxxx";                             //SSID
char pass[] = "yyyyyyy";                             //PASS

void sendSensor()
{
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
//===================================================
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
//===================================================
}

void setup()
{
  Serial.begin(9600);                   // Setup : Serial
  
  Blynk.begin(auth, ssid, pass);        // Setup : Blynk 
  timer.setInterval(1000L, sendSensor); // .
  
  dht.setup(Pin_DHT22, DHTesp::DHT22);  // Setup : DHT 
  
  lc.shutdown(0, false);                // Setup : MAX7219 
  lc.setIntensity(0, 8);                // .
  lc.clearDisplay(0);                   // .
}

void loop()
{
//================= job 1/4 : Run Blynk ======================

  Blynk.run();
  timer.run();

//================= job 2/4 : Read DHT  ======================

  float h = dht.getHumidity();
  float t = dht.getTemperature();
  
  Serial.print("Temp : ");
  Serial.print(t); 
  Serial.print(" *c\t");
  Serial.print("Humi : ");
  Serial.print(h); 
  Serial.print(" % \n");
  
//================= job 3/4 : Split_data =======================

  float t2 = t * 10;
  float h2 = h * 10;
  
  int Temp   = (int)t;
  int Temp2  = (int)t2;
  int hu     = (int)h;
  int hu2    = (int)h2;
  int Tempp2 = (Temp  / 10) % 10;
  int Tempp1 =  Temp  % 10;
  int Tempp0 =  Temp2 % 10;
  int Humi2  = (hu  / 10) % 10;
  int Humi1  =  hu  % 10;
  int Humi0  =  hu2 % 10;

//================= job 4/4 : show_MAX7219 ====================

  lc.setDigit(0, 7, Tempp2, false);
  lc.setDigit(0, 6, Tempp1, true);
  lc.setDigit(0, 5, Tempp0, false);
  lc.setRow  (0, 4, B00001101);     //c
  lc.setDigit(0, 3, Humi2, false);
  lc.setDigit(0, 2, Humi1, true);
  lc.setDigit(0, 1, Humi0, false);
  lc.setRow  (0, 0, B00010111);     //h
  
//=============================================================
  delay(2000); 
}
