#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "xxxxxxxx";
const char *password = "xxxxxxxx";
const char *Anto_URL = "https://api.anto.io/request/";
const char *tokenKey = "rn9OGPtcz9m1vfeK1seOz5fY28fQjcUqU0LkHN9s";
const char *Data1 = "/gas.91e10.price";
char *get_URL;

void setup() {
  Serial.begin(115200);
  Serial.print("\n\nconnect to");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("\nIP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  float Price_GAS95E10 = 12.34;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    strcpy(get_URL, Anto_URL);
    strcat(get_URL, tokenKey);
    strcat(get_URL, Data1);
    http.begin(get_URL);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      int nLoct = payload.indexOf(',');
      String cString = payload.substring(nLoct + 10, nLoct + 15);
      Serial.println(cString);
      Price_GAS95E10 = cString.toFloat();
    }
    http.end();
  }
  Serial.printf("gas.95e10.price = %0.2f\n", Price_GAS95E10);
  delay(30000);
}
