#include "Arduino.h"
#include "camera.h"
#include <stdio.h>
#include "ftp.h"
#include "time.h"

unsigned long frameInterval = 60000 * 5; // Every 5 minute
unsigned long lastFrameDelta = 0;
char timeStringBuff[50];

void getDate()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  strftime(timeStringBuff, sizeof(timeStringBuff), "lapse-%m-%d-%Y-%H-%M-%S.jpg", &timeinfo);

  return;
}

bool processLapse(unsigned long dt)
{
    lastFrameDelta += dt;
    if(lastFrameDelta >= frameInterval)
    {
        getDate();

        lastFrameDelta -= frameInterval;
        camera_fb_t *fb = NULL;
        esp_err_t res = ESP_OK;
        fb = esp_camera_fb_get();
        if (!fb)
        {
	        Serial.println("Camera capture failed");
	        return false;
        }

        if(!uploadFile(timeStringBuff, (unsigned char *)fb->buf, fb->len))
        {
            return false;
        }
        esp_camera_fb_return(fb);
    }
    return true;
}
