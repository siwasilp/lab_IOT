#include <WiFi.h>
#include <Time.h>
//--------------------------------------
const char* ssid      = "POND";       // your network SSID 
const char* password  = "pond2639";   // your network password
int timezone = 7 * 3600;              // ตั้งค่า TimeZone ตามเวลาประเทศไทย
int dst = 0;                          // กำหนดค่า Date Swing Time
const String month_name[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const String day_name[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  WiFi.mode(WIFI_STA);          //เชื่อมต่อ Wifi
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("*");
    delay(1000);
  }
  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");  //ดึงเวลาจาก Server
  Serial.println("\nLoading time");
  while (!time(nullptr)) {
    Serial.print("*");
    delay(1000);
  }
  Serial.println("");
}

void loop()
{
 //================= job 1/2 : get time [sever] ================
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
 //================= job 2/2 : print time [serial] =============
  Serial.print(" --> ");
  Serial.print(day_name[(p_tm->tm_wday)]);
  Serial.print(" / ");
  Serial.print(p_tm->tm_mday);
  Serial.print(" / ");
  Serial.print(month_name[(p_tm->tm_mon)]);
  Serial.print(" / ");
  Serial.print(p_tm->tm_year + 2443);
  Serial.print(" / ");
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.print(p_tm->tm_sec);
  Serial.println("");
 //========================================
  delay(1000);
}
