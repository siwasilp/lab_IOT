#include <WiFi.h>
#include "ThingSpeak.h"

WiFiClient  client;
char ssid[] = "POND";    //  your network SSID (name)
char pass[] = "pond2639";   // your network password

/*
  This is the ThingSpeak channel number for the MathwWorks weather station
  https://thingspeak.com/channels/12397.  It senses a number of things, including
  Wind Direction, Wind Speed, Humidity, Temperature, Rainfall, and Atmospheric Pressure.
  field of the channel:
  Field 1 - Wind Direction(degree where 0 is North)
  Field 2 - Wind Speed(MPH)
  Field 3 - Humidity(%RH)
  Field 4 - Temperature(Dergees F)
  Field 5 - Rainfall(inches since last measurement)
  Field 6 - Atmospheric Pressure(inHg)
*/

unsigned long weatherStationChannelNumber = 12397;

void setup() {
  Serial.begin(115200);
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
  float WindDirection = ThingSpeak.readFloatField(weatherStationChannelNumber, 1);
  float WindSpeed = ThingSpeak.readFloatField(weatherStationChannelNumber, 2);
  float Humidity = ThingSpeak.readFloatField(weatherStationChannelNumber, 3);
  float temperature = ThingSpeak.readFloatField(weatherStationChannelNumber, 4);
  float Rainfall = ThingSpeak.readFloatField(weatherStationChannelNumber, 5);
  float Pressure = ThingSpeak.readFloatField(weatherStationChannelNumber, 6);

  Serial.println("====================================================");
  Serial.println("Current weather conditions in Natick: ");
  Serial.print("temperature('F)= "); Serial.println(temperature);
  Serial.print("Humidity(%)= "); Serial.println(Humidity);
  Serial.print("Wind Speed(MPH)= "); Serial.println(WindSpeed);
  Serial.print("Wind Direction(degree)= "); Serial.println(WindDirection);
  Serial.print("Pressure(inHg)= "); Serial.println(Pressure);
  if (Rainfall > 0)Serial.println("And it's Rainy");
  else Serial.println("And it's Sunny");

  delay(60000); // Note that the weather station only updates once a minute
}
