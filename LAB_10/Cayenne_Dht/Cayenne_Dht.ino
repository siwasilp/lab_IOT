#define CAYENNE_PRINT Serial
#include "DHTesp.h"

#include <CayenneMQTTWiFi.h>
#define DHT_PIN 5

// WiFi network info.
char ssid[] = "POND";
char wifiPassword[] = "pond2639";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "e0a05510-e502-11e9-84bb-8f71124cfdfb";
char password[] = "1906c1a7a741d0fdae6b12c959075de912ab916b";
char clientID[] = "4fc0d7f0-e50b-11e9-a4a3-7d841ff78abf";

DHTesp dht;
void setup() {
  Serial.begin(115200);
  dht.setup(DHT_PIN, DHTesp::DHT22);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
}
CAYENNE_OUT_DEFAULT()
{
  float t = dht.getTemperature();
  Cayenne.virtualWrite(0,t,"temp","c");

  float h = dht.getHumidity();
  Cayenne.virtualWrite(1, h,"rel_hum","p");
}
