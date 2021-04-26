#include <WiFi.h>
#include "time.h"
#include "camera.h"
#include "lapse.h"

//NTP
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

//WIFI
const char *ssid = "ChangeMe";
const char *password = "ChangeMe";

void startCameraServer();

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "lapse-%m-%d-%Y-%H-%M-%S.jpg");
}

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  initCamera();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  startCameraServer();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  printLocalTime();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop()
{
  unsigned long t = millis();
  static unsigned long ot = 0;
  unsigned long dt = t - ot;
  ot = t;
  processLapse(dt);
}
