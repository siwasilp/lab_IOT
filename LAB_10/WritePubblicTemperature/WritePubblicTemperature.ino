#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHTesp.h"

#define dhtPin 5

char ssid[] = "POND";    //  your network SSID (name)
char pass[] = "pond2639";   // your network password
unsigned long myChannelNumber = 877765;
const char* myWriteAPIKey = "KY6FZHJHIDCD6RJA";
const char* myReadAPIKey = "IFBJWZ1LNQ10GRI3";

WiFiClient  client;
DHTesp dht;
void setup() {
  Serial.begin(115200);
  dht.setup(dhtPin, DHTesp::DHT22);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);

}

void loop() {
  float h = dht.getHumidity();
  float t = dht.getTemperature();
  Serial.print("\nTemperature('C)= ");
  Serial.print(t, 1);
  Serial.print("\tHumidity(%)= ");
  Serial.print(h, 1);
  Serial.println();
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  for(int i ='Z';i>='A';i--){
    Serial.write(i);
    delay(2000);
  }
}
