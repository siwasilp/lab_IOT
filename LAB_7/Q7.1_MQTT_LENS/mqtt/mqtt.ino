#include <DHTesp.h>
#include <WiFi.h>
#include <PubSubClient.h>

DHTesp dht;
int LED1 = 18;
int LED2 = 19;
int LED3 = 21;
int LED4 = 22;

const char* ssid        = "xxxxxxxxxx";
const char* password    = "yyyyyyyyyy";
const char* mqtt_server = "mqtt.eclipse.org";
const char* toTopic     = "sexy_sut";          
const char* mySubscribe = "sexy_sut";            

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the BUILTIN_LED 
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
  digitalWrite(LED4,HIGH);
  dht.setup(15);
  Serial.begin(115200);

  // Wifi Connect
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // MQTT Connect
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  for (int i = 0; i < length; i++)  msg += (char)payload[i];
  Serial.println(msg);

  readSubscribe(msg);  // เอาข้อความจากกระดานไปทำอะไรบางอย่าง [subscribe]***

  Serial.println();
}

void publishToTopic(String mStr) { //ส่งข้อความขึ้นกระดาน
  client.publish(toTopic, mStr.c_str());  //คำสั่งส่งข้อความ toTopic คือกระดาน , mStr คือข้อความ
  Serial.print("Publish ");
  Serial.print(mStr);
  Serial.print(" to ");
  Serial.print(toTopic);
}

void readSubscribe(String msg) {   // เอาข้อความมาแล้วทำอะไรบางอย่าง [subscribe]***
  msg.trim();
  Serial.println(msg);
  if (msg == "LED_ON") digitalWrite(LED_BUILTIN, HIGH);
  else if (msg == "LED_OFF") digitalWrite(LED_BUILTIN, LOW);

  if (msg == "LED1_ON") digitalWrite(LED1, LOW);
  else if (msg == "LED1_OFF") digitalWrite(LED1, HIGH);

  if (msg == "LED2_ON") digitalWrite(LED2, LOW);
  else if (msg == "LED2_OFF") digitalWrite(LED2, HIGH);

  if (msg == "LED3_ON") digitalWrite(LED3, LOW);
  else if (msg == "LED3_OFF") digitalWrite(LED3, HIGH);

  if (msg == "LED4_ON") digitalWrite(LED4, LOW);
  else if (msg == "LED4_OFF") digitalWrite(LED4, HIGH);
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("MQTT Connected");
      // ... and resubscribe
      String clientId = "ESP32 Client-";
      clientId += String(random(0xffff), HEX);
      if (client.connect(clientId.c_str()))
        client.subscribe(mySubscribe);    //กระดานที่เราติดตาม [subscribe]***
    } else {
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  else{

    // อ่านค่า t , h
    float temp = dht.getTemperature();
    float humi = dht.getHumidity();

    // จัดเรียง pack DATA ก่อนนำส่ง [msg]
    String msg = "";
    msg += "Temperature = ";
    msg += temp;
    msg += ", Humidity = ";
    msg += humi;
    msg += "%";

    publishToTopic(msg); //ข้อความที่ส่งขึ้นไปบนกระดาน [publishToTopic]**
    
  }
  delay(2000);
  client.loop();
}
