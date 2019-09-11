//==== BLYNK : DHT LED ========

#define    BLYNK_PRINT Serial
#include   <WiFi.h>
#include   <WiFiClient.h>
#include   <BlynkSimpleEsp32.h>
BlynkTimer timer;s

//=========================================

#include   "DHTesp.h"
#include   <DHTesp.h>
#define    Pin_DHT22  15          //pin DHT
DHTesp     dht;

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

}

void loop()
{
//================= job 1/2 : Run Blynk ======================

  Blynk.run();
  timer.run();

//================= job 2/2 : Read DHT  ======================

  float h = dht.getHumidity();
  float t = dht.getTemperature();
  
  Serial.print("Temp : ");
  Serial.print(t); 
  Serial.print(" *c\t");
  Serial.print("Humi : ");
  Serial.print(h); 
  Serial.print(" % \n");
  
//=============================================================
  delay(2000); 
}
