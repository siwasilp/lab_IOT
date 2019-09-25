#include <AntoIO.h>
#include "DHTesp.h";
#include "LedControl.h"

#define LED_1 15
#define LED_2 2
#define SW_01 18
#define SW_02 19
#define Pin_DHT 5
#define Pin_DIN 4
#define Pin_CS 22
#define Pin_CLK 23


int sts_SW_01, sts_SW_02, Counter;

const char *ssid = "xxxxxxxxx";   //*
const char *pass = "yyyyyyyyy";   //*
const char *user = "aaaaaaaaa";   //*
const char *token = "rn9OGPtcz9m1vfeK1seOz5fY28fQjcUqU0LkHN9s";  //*

const char *thing = "Tesy_IOT";
const char *channel1 = "LED_01";
const char *channel2 = "LED_02";
const char *channel3 = "LED_03";
const char *channel4 = "LED_04";
const char *channel5 = "SW_01";
const char *channel6 = "SW_02";
const char *channel7 = "temp";
const char *channel8 = "humd";

/* create AntoIO instance */
LedControl lc = LedControl(Pin_DIN, Pin_CS, Pin_CLK, 1);
AntoIO anto(user, token, thing);
DHTesp dht;

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(SW_01, INPUT_PULLUP);
  pinMode(SW_02, INPUT_PULLUP);
  dht.setup(Pin_DHT, DHTesp::DHT22);

  Serial.begin(115200);
  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");

  while (!anto.wifi.begin(ssid, pass));
  Serial.println("\nConnected, trying to connect to broker...");

  while (!anto.mqtt.connect(user, token, true));
  Serial.println("\nConnected");

  /* change "digital-channel" to your channel in switch type */
  anto.mqtt.sub(channel1);
  anto.mqtt.sub(channel2);
  anto.mqtt.sub(channel3);
  anto.mqtt.sub(channel4);
  anto.mqtt.sub(channel5);
  anto.mqtt.sub(channel6);
  anto.mqtt.sub(channel7);
  anto.mqtt.sub(channel8);
}

void loop() {
  anto.mqtt.loop();
  /*
     for proper functionality,
     10-second delay should be added after loop()
  */
  if (sts_SW_01 != digitalRead(SW_01)) {
    sts_SW_01 = digitalRead(SW_01);
    anto.mqtt.pub(channel5, sts_SW_01);
    Serial.print("status SW1 ="); Serial.println(sts_SW_01);
    delay(100);
  }
  if (sts_SW_02 != digitalRead(SW_02)) {
    sts_SW_02 = digitalRead(SW_02);
    anto.mqtt.pub(channel6, sts_SW_02);
    Serial.print("status SW2 ="); Serial.println(sts_SW_02);
    delay(100);
  }
  Counter++;
  if (Counter % 200 == 0) Publish_Display();
  delay(10);
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();

  if (topic.indexOf(channel1) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(LED_1, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(LED_1, LOW);
      Serial.println("LOW");
    }
  };
  if (topic.indexOf(channel2) != -1) {
    if (payload.toInt() == 1) {
      digitalWrite(LED_2, HIGH);
      Serial.println("HIGH");
    } else {
      digitalWrite(LED_2, LOW);
      Serial.println("LOW");
    }
  };
}
void Publish_Display() {
  float temp = dht.getTemperature();
  float humi = dht.getHumidity();
  Serial.print("Humidity: "); Serial.print(humi);
  Serial.print(" Temperature: "); Serial.println(temp);

  anto.mqtt.pub(channel7, temp);
  anto.mqtt.pub(channel8, humi);

  int t = temp * 10; int t1 = t / 100; int t2 = t / 10 % 10; int t3 = t % 10;
  int h = humi * 10; int h1 = h / 100; int h2 = h / 10 % 10; int h3 = h % 10;

  lc.setDigit(0, 7, t1, false);
  lc.setDigit(0, 6, t2, true);
  lc.setDigit(0, 5, t3, false);
  lc.setRow(0, 4, B00001101);
  lc.setDigit(0, 3, h1, false);
  lc.setDigit(0, 2, h2, true);
  lc.setDigit(0, 1, h3, false);
  lc.setRow(0, 0, B00010111);
  delay(300);
}
