#include <WiFi.h>
#include "ThingSpeak.h"
#define LED_01 22
#define LED_02 23

char ssid[] = "XXXXXX";    //  your network SSID (name)
char pass[] = "XXXXXX";   // your network password
unsigned long myChannelNumber = 123456;
const char* myWriteAPIKey = "KY6FZHJHIDCD6RJA";
const char* myReadAPIKey = "IFBJWZ1LNQ10GRI3";

WiFiClient  client;
void setup() {
  Serial.begin(115200);
  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
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
  int Cmd_LED = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
  Serial.print("Last Data is: ");
  Serial.println(Cmd_LED);
  if (Cmd_LED == 1)digitalWrite(LED_01, HIGH);
  if (Cmd_LED == 2)digitalWrite(LED_01, LOW);
  if (Cmd_LED == 3)digitalWrite(LED_02, HIGH);
  if (Cmd_LED == 4)digitalWrite(LED_02, LOW);
  if (Cmd_LED == 9) {
    digitalWrite(LED_01, HIGH);
    digitalWrite(LED_02, HIGH);
  }
  if (Cmd_LED == 0) {
    digitalWrite(LED_01, LOW);
    digitalWrite(LED_02, LOW);
  }
  delay(30000);

}
