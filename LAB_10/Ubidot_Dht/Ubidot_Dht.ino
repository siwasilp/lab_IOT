#include <DHTesp.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define WIFISSID "xxxxxx"
#define PASSWORD "xxxxxx"
#define TOKEN "BBFF-tnCQhEQRd5MoJs8eKiiFj7VOktditG"
#define MQTT_CLIENT_NAME "xxxxxx"
#define VARIABLE_LABEL "TEMP"
#define VARIABLE_LABEL1 "HUMD"
#define DEVICE_LABEL "ESP8266"
char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char str_tem[6];
char str_hum[6];
WiFiClient ubidots;
PubSubClient client(ubidots);
DHTesp dht;
int dhtPin = 2;
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  Serial.println();
  Serial.print("Wait for WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  // client.setCallback(callback);
  dht.setup(dhtPin, DHTesp::DHT11);
  Serial.println("DHT initiated");
}
void loop() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.println(temperature, 1);
  delay(1000);
  if (!client.connected()) {
    reconnect();
  }
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL);
  dtostrf(temperature , 4 , 2, str_tem);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_tem);
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL1);
  dtostrf(humidity , 4 , 2, str_hum);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_hum);
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  client.loop();
  delay(1000);
}
void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}
