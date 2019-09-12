T3:

กด switch1 เปลี่ยนไปโหมด 1

กด switch2 เปลี่ยนไปโหมด 2

Mode1: พริบเป็นจังหวะชีพจร ไปเรื่อยๆ

Mode2: กระพริบตามจำนวนที่ป้อนผ่าน Serial Monitor

#define LED1 5
#define LED2 18
#define LED3 19
#define LED4 21
#define SW1 22
#define SW2 23
int m = 1;
int t = 0;
void setup() {
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
pinMode(SW1, INPUT_PULLUP);
pinMode(SW2, INPUT_PULLUP);
Serial.begin(115200);
}
void loop() {
int readSW1 = digitalRead(SW1);
int readSW2 = digitalRead(SW2);
Serial.print(readSW1);
Serial.println(readSW2);
if (Serial.available() > 0) {
t = Serial.parseInt();
Serial.print("T = ");
Serial.println(t);
}
if (readSW1 == 0) {
m = 1;
}
else if (readSW2 == 0) {
m = 2;
}
if (m == 1) {
digitalWrite(LED1, HIGH);
digitalWrite(LED2, HIGH);
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
delay(250);
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
delay(250);
digitalWrite(LED1, HIGH);
digitalWrite(LED2, HIGH);
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
delay(250);
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
delay(250 * 3);
}
else if (m == 2) {
for (t ; t > 0 ; t-- ) {
digitalWrite(LED1, HIGH);
digitalWrite(LED2, HIGH);
digitalWrite(LED3, HIGH);
digitalWrite(LED4, HIGH);
delay(250);
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
delay(250);
}
}
}



*************************************************************

ติว T2:

กด SW1 กับ SW2 พร้อมกัน MAX7219 ดับ

กด SW1 MAX7219 แสดง อุณหภูมิและความชื้น

กด SW2 MAX7219 แสดง รหัสนักศึกษาตัวเอง

 #include "LedControl.h"
LedControl lc = LedControl(5, 19, 18, 1);
#include "DHTesp.h"
DHTesp dht;
#define sw1 22
#define sw2 23
void setup() {
Serial.begin(115200);
dht.setup(4, DHTesp::DHT22);
lc.shutdown(0, false);
/* Set the brightness to a medium values */
lc.setIntensity(0, 8);
/* and clear the display */
lc.clearDisplay(0);
pinMode(sw1,INPUT_PULLUP);
pinMode(sw2,INPUT_PULLUP);
}
void loop() {
float h = dht.getHumidity();
float t = dht.getTemperature();
Serial.print(h);
Serial.println(t);
int readsw1 = digitalRead(sw1);
int readsw2 = digitalRead(sw2);
Serial.print(readsw1);
Serial.println(readsw2);
if(readsw1 == 0 && readsw2 == 0){
lc.setRow(0,7,0);
lc.setRow(0,6,0);
lc.setRow(0,5,0);
lc.setRow(0,4,0);
lc.setRow(0,3,0);
lc.setRow(0,2,0);
lc.setRow(0,1,0);
lc.setRow(0,0,0);
}
else if(readsw1 == 0){
int h0 = h *10;
int t0 = t*10;
lc.setDigit(0,5,t0%10,false);t0/=10;
lc.setDigit(0,6,t0%10,true);t0/=10;
lc.setDigit(0,7,t0%10,false);t0/=10;
lc.setRow(0,4,B00001101);
lc.setDigit(0,1,h0%10,false);h0/=10;
lc.setDigit(0,2,h0%10,true);h0/=10;
lc.setDigit(0,3,h0%10,false);h0/=10;
lc.setRow(0,0,B00010111);
}
else if(readsw2 == 0){
lc.setRow(0,7,B00011111);
lc.setDigit(0,6,5,false);
lc.setDigit(0,5,9,false);
lc.setDigit(0,4,0,false);
lc.setDigit(0,3,8,false);
lc.setDigit(0,2,4,false);
lc.setDigit(0,1,3,false);
lc.setDigit(0,0,1,false);
}
}

*************************************************************

ติวข้อ1

อยากได้ 2 Mode

Mode แรก นับ ขึ้นเอง ตั้งแต่ 0 ถึงรหัสนักศึกษา4ตัวท้าย ของตัวเอง แล้วกลับมา 0

Mode สอง กดปุ่มแล้วนับขึ้นที่ล่ะ10 ตั้งแต่ 0 -9999 โดยค่าต้องไม่เกิน 9999

 #include "LedControl.h"
#define Mode_SW 23
#define Up_SW 22
#define Myid 8431
int count = 0;
int Mode = 1;
LedControl lc=LedControl(5,19,18,1);
void setup() {
Serial.begin(115200);
pinMode(Mode_SW , INPUT_PULLUP);
pinMode(Up_SW , INPUT_PULLUP);
lc.shutdown(0,false);
lc.setIntensity(0,8);
lc.clearDisplay(0);
}
void Auto(){
count++;
if(count >= Myid){
count = 0;
}
}
void Manual(){
int Read_UPSW = digitalRead(Up_SW);
Serial.println(Read_UPSW);
if(Read_UPSW == 0){
count+=10;
if(count >= 9999){
count = 0;
}
}
}
void loop() {
int Read_Mode_SW = digitalRead(Mode_SW);
Serial.print(Read_Mode_SW);
if(Read_Mode_SW == 0){
Mode = Mode * -1 ; 
}
if(Mode == 1){
Auto();
}
else if(Mode == -1){
Manual();
}
int temp = count;
lc.setDigit(0,0,temp%10,false) ;temp/=10;
lc.setDigit(0,1,temp%10,false) ;temp/=10;
lc.setDigit(0,2,temp%10,false) ;temp/=10;
lc.setDigit(0,3,temp%10,false) ;temp/=10;
delay(100);
}

*******************************************************
Q4. DHT + 4 LED

Source Code:

#include <WiFi.h>

#include <WebServer.h>

#define SSID "MrZacK"

#define PASSWORD "12345678"

#include <DHTesp.h>

WiFiServer server(80);

DHTesp dht;

String header;

int stateLed1, stateLed2, stateLed3, stateLed4;

int led1 = 5 , led2 = 18 , led3 = 19 , led4 = 21;

void setup()

{

Serial.begin(115200);

pinMode(led1, OUTPUT);

pinMode(led2, OUTPUT);

pinMode(led3, OUTPUT);

pinMode(led4, OUTPUT);

digitalWrite(led1, HIGH);

digitalWrite(led2, HIGH);

digitalWrite(led3, HIGH);

digitalWrite(led4, HIGH);

WiFi.begin(SSID, PASSWORD);

Serial.printf("WiFi connecting to %s\n", SSID);

while (WiFi.status() != WL_CONNECTED) {

Serial.print(".");

delay(400);

}

Serial.printf("\nWiFi connected\nIP : ");

Serial.println(WiFi.localIP());

dht.setup(23, DHTesp::DHT22);

server.begin();

}

void loop() {

float humidity = dht.getHumidity();

float temperature = dht.getTemperature();

/// เขาส่งมาแล้วเรารับไว้

WiFiClient client = server.available();

if (client) {

Serial.println("New Client.");

String currentLine = "";

while (client.connected()) {

if (client.available()) {

char c = client.read();

Serial.write(c);

header += c;

/////////////////////////////////////////

// Control LED

if (header.indexOf("GET /LED1/on") >= 0) {

stateLed1 = 1;

digitalWrite(led1, LOW);

}

else if (header.indexOf("GET /LED1/off") >= 0) {

stateLed1 = 0;

digitalWrite(led1, HIGH);

}

if (header.indexOf("GET /LED2/on") >= 0) {

stateLed2 = 1;

digitalWrite(led2, LOW);

}

else if (header.indexOf("GET /LED2/off") >= 0) {

stateLed2 = 0;

digitalWrite(led2, HIGH);

}

if (header.indexOf("GET /LED3/on") >= 0) {

stateLed3 = 1;

digitalWrite(led3, LOW);

}

else if (header.indexOf("GET /LED3/off") >= 0) {

stateLed3 = 0;

digitalWrite(led3, HIGH);

}

if (header.indexOf("GET /LED4/on") >= 0) {

stateLed4 = 1;

digitalWrite(led4, LOW);

}

else if (header.indexOf("GET /LED4/off") >= 0) {

stateLed4 = 0;

digitalWrite(led4, HIGH);

}

//////////////////////////////////////////////////////////////

if (c == '\n') {

if (currentLine.length() == 0) {

//// Web page

// หัวเว็บ

client.println("HTTP/1.1 200 OK");

client.println("Content-type:text/html");

client.println();

//////////////////////////////////////////

client.print("Temperature > "); client.print(temperature, 2);

client.print("'C. Humidity > "); client.print(humidity, 2);

client.print("%H.");

if (stateLed1 == 1) {

client.println("<br><p><a href=\"/LED1/off\"><button >LED1 ON</button></a></p>");

} else {

client.println("<br><p><a href=\"/LED1/on\"><button>LED1 OFF</button></a></p>");

}

if (stateLed2 == 1) {

client.println("<br><p><a href=\"/LED2/off\"><button >LED2 ON</button></a></p>");

} else {

client.println("<br><p><a href=\"/LED2/on\"><button >LED2 OFF</button></a></p>");

}

if (stateLed3 == 1) {

client.println("<br><p><a href=\"/LED3/off\"><button>LED3 ON</button></a></p>");

} else {

client.println("<br><p><a href=\"/LED3/on\"><button >LED3 OFF</button></a></p>");

}

if (stateLed4 == 1) {

client.println("<br><p><a href=\"/LED4/off\"><button >LED4 ON</button></a></p>");

} else {

client.println("<br><p><a href=\"/LED4/on\"><button >LED4 OFF</button></a></p>");

}

// The HTTP response ends with another blank line:

client.println();

// break out of the while loop:

break;

}

}

}

}

// close the connection:

client.stop();

Serial.println("Client Disconnected.");

}

Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");

delay(50);

header = "";

}

*******************************************************

Problem : มี LED 4 หลอด มี 3 States 
-> State 1 : Idle state กระพิบไฟ Delay 200 ms
-> State 2 : L -> R 
-> State 3 : L <- R

Source Code:

#include "LedControl.h"

// Define variables

#define Mode_SW 23

#define LED1 5

#define LED2 18

#define LED3 19

#define LED4 21

int Mode = 0;

void setup() {

Serial.begin(115200);

// Initial setup button and led

pinMode(Mode_SW , INPUT_PULLUP);

pinMode(LED1 , OUTPUT);

pinMode(LED2 , OUTPUT);

pinMode(LED3 , OUTPUT);

pinMode(LED4 , OUTPUT);

}

void M1(){ // Blink

digitalWrite(LED1,LOW);digitalWrite(LED2,LOW);digitalWrite(LED3,LOW);digitalWrite(LED4,LOW);

delay(200);

digitalWrite(LED1,HIGH);digitalWrite(LED2,HIGH);digitalWrite(LED3,HIGH);digitalWrite(LED4,HIGH);

delay(200);

}

void M2(){ // L -> R

digitalWrite(LED1,LOW);digitalWrite(LED2,HIGH);digitalWrite(LED3,HIGH);digitalWrite(LED4,HIGH);

delay(200);

digitalWrite(LED1,HIGH);digitalWrite(LED2,LOW);digitalWrite(LED3,HIGH);digitalWrite(LED4,HIGH);

delay(200);

digitalWrite(LED1,HIGH);digitalWrite(LED2,HIGH);digitalWrite(LED3,LOW);digitalWrite(LED4,HIGH);

delay(200);

digitalWrite(LED1,HIGH);digitalWrite(LED2,HIGH);digitalWrite(LED3,HIGH);digitalWrite(LED4,LOW);

delay(200);

}

void M3(){ // L <- R

digitalWrite(LED1,HIGH);digitalWrite(LED2,HIGH);digitalWrite(LED3,HIGH);digitalWrite(LED4,LOW);

delay(200);

digitalWrite(LED1,HIGH);digitalWrite(LED2,HIGH);digitalWrite(LED3,LOW);digitalWrite(LED4,HIGH);

delay(200);

digitalWrite(LED1,HIGH);digitalWrite(LED2,LOW);digitalWrite(LED3,HIGH);digitalWrite(LED4,HIGH);

delay(200);

digitalWrite(LED1,LOW);digitalWrite(LED2,HIGH);digitalWrite(LED3,HIGH);digitalWrite(LED4,HIGH);

delay(200);

}

void loop() {

// Button Input

int Read_Mode_SW = digitalRead(Mode_SW);

Serial.print(Read_Mode_SW);

//Control Mode

if (Read_Mode_SW == 0) {

if (Mode == 0) Mode = 1;

else if (Mode == 1) Mode = 2;

else if (Mode == 2) Mode = 0;

}

// Mode Selector

if (Mode == 0) M1();

else if (Mode == 1) M2();

else if (Mode == 2) M3();

}


*******************************************************
 #include "TM1636.h"
#include "TickTockShield.h"
TickTockShield ticktockshield;
extern int8_t disp[4];
#define LED4 5
#define LED3 4
#define LED2 3
#define LED1 2
void setup() 
{
Serial.begin(9600);
ticktockshield.init();
}
int count=0;
void loop() 
{
int x = count;
disp[3] = x%10; x=x/10;
disp[2] = x%10; x=x/10;
disp[1] = x%10; x=x/10;
disp[0] = x%10; x=x/10;
count++;
tm1636.display(disp);
digitalWrite(LED1, HIGH); delay(200); digitalWrite(LED1, LOW); delay(200);
digitalWrite(LED2, HIGH); delay(200); digitalWrite(LED2, LOW); delay(200);
digitalWrite(LED3, HIGH); delay(200); digitalWrite(LED3, LOW); delay(200);
digitalWrite(LED4, HIGH); delay(200); digitalWrite(LED4, LOW); delay(200);
}

*******************************************************

int pushButtonM = 11;

int pushButtonU = 10;

int pushButtonD = 9;

int d1 = 1;

int d2 = 2;

int d3 = 3;

int d4 = 4;

int s = 6;

#include "TM1636.h"

TM1636 tm1636(7, 8);

void setup() {

tm1636.init();

Serial.begin(9600);

pinMode(d1, OUTPUT);

pinMode(d4, OUTPUT);

pinMode(d2, OUTPUT);

pinMode(d2, OUTPUT);

pinMode(s, OUTPUT);

pinMode(pushButtonM, INPUT_PULLUP);

pinMode(pushButtonU, INPUT_PULLUP);

pinMode(pushButtonD, INPUT_PULLUP);

}

void loop() {

int8_t DispBuff[4];

//ชุดของM

int buttonStateM = digitalRead(pushButtonM);

Serial.print(buttonStateM);

if (buttonStateM == 0) {

digitalWrite(d1, HIGH);

digitalWrite(d2, HIGH);

digitalWrite(d3, HIGH);

digitalWrite(d4, HIGH);

digitalWrite(s, HIGH);

delay(100);

digitalWrite(d1, LOW);

digitalWrite(d2, LOW);

digitalWrite(d3, LOW);

digitalWrite(d4, LOW);

digitalWrite(s, LOW);

delay(100);

}

delay(1);

// U

int buttonStateU = digitalRead(pushButtonU);

Serial.print(buttonStateU);

if (buttonStateU == 0) {

digitalWrite(d1, HIGH); delay(100);

digitalWrite(d1, LOW); delay(100);

digitalWrite(d2, HIGH);delay(100);

digitalWrite(d2, LOW); delay(100);

digitalWrite(d3, HIGH);delay(100);

digitalWrite(d3, LOW); delay(100);

digitalWrite(d4, HIGH);delay(100);

digitalWrite(d4, LOW); delay(100);

}

delay(1);

//D

int buttonStateD = digitalRead(pushButtonD);

Serial.println(buttonStateD);

if (buttonStateD == 0) {

digitalWrite(d4, HIGH); delay(100);

digitalWrite(d4, LOW); delay(100);

digitalWrite(d3, HIGH);delay(100);

digitalWrite(d3, LOW); delay(100);

digitalWrite(d2, HIGH);delay(100);

digitalWrite(d2, LOW); delay(100);

digitalWrite(d1, HIGH);delay(100);

digitalWrite(d1, LOW); delay(100);

}

delay(1);

}

*******************************************************

 #include <TimerOne.h>
#include "Wire.h"
#include "TM1636.h"
#define M 11
#define U 10
#define D 9
TM1636 tm1636(7,8);
int i=0;
void setup() {
tm1636.init();
pinMode(M, INPUT_PULLUP);
digitalWrite(M, HIGH);
pinMode(U, INPUT_PULLUP);
digitalWrite(U, HIGH);
pinMode(D, INPUT_PULLUP);
digitalWrite(D, HIGH);
}
void loop() {
int8_t DispBuff[4];
if(digitalRead(M) == 0){
i=0;
}
if(digitalRead(U) == 0){
i++;
}
if(digitalRead(D) == 0){
i--;
}
if(i<0){
i=0;
}
if(i>9999){
i=9999;
}
int a = i%10;
int b = ((i%100) - i0)/10;
int c = ((i%1000) - i1 -i0)/100;
int d = (i/1000);
DispBuff[0]=d;
DispBuff[1]=c;
DispBuff[2]=b;
DispBuff[3]=a;
tm1636.display(DispBuff);
}

*******************************************************

 #include <TimerOne.h>
#include "Wire.h"
#include "TM1636.h"
#define DEBUG 1
#define KEY_MENU 11
#define KEY_UP 10
#define KEY_DOWN 9
TM1636 tm1636(7, 8);
int i = 0;
void setup() {
Serial.begin(115200);
tm1636.init();
pinMode(KEY_MENU, INPUT_PULLUP);
digitalWrite(KEY_MENU, HIGH);
pinMode(KEY_UP, INPUT_PULLUP);
digitalWrite(KEY_UP, HIGH);
pinMode(KEY_DOWN, INPUT_PULLUP);
digitalWrite(KEY_DOWN, HIGH);
}
int st = 0;
void loop() {
int8_t DispBuff[4];
if (digitalRead(KEY_MENU) == LOW) {
if (st == 0 || st == 2) {
st = 1;
}else if (st == 1) {
st = 2;
}
}
if (st == 2) {
if (digitalRead(KEY_UP) == LOW) {
i += 10;
}
if (digitalRead(KEY_DOWN) == LOW) {
i -= 10;
}
if (i < 0) {
i = 0;
}
if (i > 9999) {
i = 9999;
}
int i0 = i % 10;
int i1 = ((i % 100) - i0) / 10;
int i2 = ((i % 1000) - i1 - i0) / 100;
int i3 = (i / 1000);
DispBuff[0] = i3;
DispBuff[1] = i2;
DispBuff[2] = i1;
DispBuff[3] = i0;
tm1636.display(DispBuff);
} else if (st == 1) {
i+=10;
int i0 = i % 10;
int i1 = ((i % 100) - i0) / 10;
int i2 = ((i % 1000) - i1 - i0) / 100;
int i3 = (i / 1000);
DispBuff[0] = i3;
DispBuff[1] = i2;
DispBuff[2] = i1;
DispBuff[3] = i0;
tm1636.display(DispBuff);
if (i == 9999) {
i = 0;
}
}
}

*******************************************************
#include <iostream>

#include<limits>

#include <cstdlib>

#include <ctime>

using namespace std;

void output(string [], int [], string []);

int main() {

struct game {

string title[4];

int year[4];

string company[4];

};

struct game action[4], survival[4];

int i;

for(i=0;i<4;i++){

if(i<2){

cout << "Action game [" << i+1 << "]" << endl;

cout << "Enter game title: " ;

cin.clear();

getline(cin,action[i].title[i]);

cout << "Enter release year: ";

cin >> action[i].year[i];

cout << "Enter company: ";

cin.ignore(numeric_limits<streamsize>::max(),'\n');

getline(cin,action[i].company[i]);

cout << endl;

}else{

cout << "Survival game [" << i+1 << "]" << endl;

cout << "Enter game title: " ;

cin.getline(action[i].title[i],30);

cout << "Enter release year: ";

cin >> survival[i].year[i];

cout << "Enter company: ";

cin.ignore(numeric_limits<streamsize>::max(),'\n');

getline(cin,survival[i].company[i]);

cout << endl;

}

}

string name,lastname;

cout << "Enter last-named: ";

cin >> lastname;

cout << "Enter name: ";

cin >> name;

// output(string [], int [], string [])

}

*******************************************************
void setup() {
Serial.begin(9600);
}
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
for (int i = 1; i <= n; i++) {
for (int j = 1; j <= n; j++) {
Serial.print("X ");
}
Serial.println();
}
}
}

*******************************************************
void setup() {
Serial.begin(9600);
}
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
if (n >= 1 && n <= 9) {
for (int i = 1; i <= n; i++) {
for (int j = 1; j <= n; j++) {
if (i == 1 || j == 1 || j == n || i == n || i == j || i + j == n + 1) {
Serial.print("X ");
} else {
Serial.print(" ");
}
}
Serial.println();
}
}
}
}

*******************************************************
void setup() {
Serial.begin(9600);
}
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
if (n >= 1 && n <= 9) {
for (int i = 1; i <= 9; i++) {
for (int j = 1; j <= n; j++) {
Serial.print("X "); 
}
Serial.println();
}
}
}
}
*******************************************************
void setup() {
Serial.begin(9600);
}
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
for (int i = 1; i <= n; i++) {
for (int j = 1; j <= n * 2 ; j++) {
if (j <= i) {
Serial.print(" ");
} else if (j <= n - i + 2) {
int c = j % 2;
Serial.print(c);
Serial.print(" ");
}
}
Serial.println();
}
}
}

*******************************************************
void setup() {
Serial.begin(9600);
}
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
for (int i = 1; i <= n * 2; i++) {
for (int j = 1; j <= abs(n - i); j++)
{
Serial.print(" ");
}
for (int j = 1; j <= 2 * (n - abs(n - i)) - 1; j++ )
{
if (j == 1 || j == 2 * (n - abs(n - i)) - 1)
Serial.print("*");
else
Serial.print(" ");
}
Serial.println();
}
}
}

*******************************************************
void setup() {
Serial.begin(9600);
}
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
for (int i = 1; i <= n * 2; i++) {
for (int j = 1; j <= n * 2; j++) {
if (j <= abs(n - i)) {
Serial.print(" ");
} else if (j <= (n - abs(n - i))) {
int c = j % 2;
Serial.print(c);
}
}
Serial.println();
}
}
}

*******************************************************
void setup() {
Serial.begin(9600);
}
int i2, j2 = 0;
void loop() {
if (Serial.available() > 0) {
int n = Serial.parseInt();
Serial.print("Input = ");
Serial.println(n);
for (int i = 1; i <= n * 2; i++) {
i2 = n - abs(n - i);
for (int j = 1; j <= abs(n - i); j++) {
Serial.print(" ");
}
for (int j = 1; j <= 2 * (n - abs(n - i)) - 1; j++ ){
j2++;
int c = value(i2, j2);
Serial.print(c);
}
j2 = 0;
Serial.println();
}
}
}
int value(int a, int b) {
return a - abs(a - b);
}

*******************************************************
 //ข้อแมวน้อย ครับ
#include "BigNumber.h"
void setup ()
{
Serial.begin (115200);
BigNumber::begin (); // initialize library
} 
void loop () 
{ 
int T = 0;
BigNumber Mea = "3";
BigNumber MTotal = "3";
for(int i=0;i<=15;i++){
Serial.print ("T > "); Serial.print (T);
Serial.print (", Mae > "); Serial.print (Mea);
Serial.print (", Total >"); Serial.println (MTotal*(BigNumber)2);
T++;
Mea =MTotal * (BigNumber)3;
MTotal = MTotal + Mea ;
}
while (1);
}


*******************************************************

#include "LedControl.h"
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
LedControl lc = LedControl(12, 11, 10, 1);
DHT dht(DHTPIN, DHTTYPE);
void setup() {
lc.shutdown(0, false);
lc.setIntensity(0, 8);
lc.clearDisplay(0);
Serial.begin(9600);
Serial.println("DHTxx test!");
dht.begin();
}

void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
float hic = dht.computeHeatIndex(t, h, false);
float hif = dht.computeHeatIndex(f, h);

lc.setDigit(0, 3, 2, false);
lc.setDigit(0, 2, 3, true);
lc.setDigit(0, 1, 0, false);
lc.setRow(0, 7, B00000000);
lc.setDigit(0, 3, 3, false);
lc.setDigit(0, 2, 3, true);
lc.setDigit(0, 1, 2, false);
lc.setRow(0, 7, B00000000);
}