#include <WiFi.h>
#include "time.h"
#include "camera.h"
#include "lapse.h"

// BOARD SETTINGS
// ESP32 Wrover Module, Minimal SPIFFS (1.9, w/OTA, 190kB SPIFFS), QIO, 80MHz, 460800, None, Disabled)

//NTP
const char* ntpServer = "au.pool.ntp.org";
const long  gmtOffset_sec = 39600;
const int   daylightOffset_sec = 0;

//WIFI
const char *ssid = "****";
const char *password = "****";

void startCameraServer();

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "lapse-%Y-%m-%d-%H-%M-%S.jpg");
}

void setup()
{
  pinMode(4, OUTPUT);
  Serial.begin(230400);
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

  Serial.println(" == TESTING FLASH LED == ");
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW)
  delay(100);
}

void loop()
{
  unsigned long t = millis();
  static unsigned long ot = 0;
  unsigned long dt = t - ot;
  ot = t;
  processLapse(dt);
}
