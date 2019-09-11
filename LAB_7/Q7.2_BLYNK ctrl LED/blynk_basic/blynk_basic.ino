#define    BLYNK_PRINT Serial
#include   <WiFi.h>
#include   <WiFiClient.h>
#include   <BlynkSimpleEsp32.h>
BlynkTimer timer;

char auth[] = "3YLex9xj0s9xdlUSoXCrXxBCoY2Nu5RT";    //Token
char ssid[] = "xxxxxxx";                             //SSID
char pass[] = "yyyyyyy";                             //PASS

void setup()
{
  Serial.begin(9600);                   // Setup : Serial
  Blynk.begin(auth, ssid, pass);        // Setup : Blynk
  timer.setInterval(1000L, sendSensor); // .
}

void loop()
{
  Blynk.run();
  timer.run();
}
