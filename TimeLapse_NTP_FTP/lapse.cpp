#include "Arduino.h"
#include "camera.h"
#include <stdio.h>
#include "ftp.h"
#include "time.h"

unsigned long frameInterval = 30000; // Every 30s (30 * 1000 = 30000)
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
        Serial.print(lastFrameDelta);
        Serial.print(" ");
        Serial.println(dt);
        // turn flash on
        digitalWrite(4, HIGH);
        // let WB + AGC settle
        delay(3000);
        getDate();

        lastFrameDelta -= frameInterval;
        camera_fb_t *fb = NULL;
        esp_err_t res = ESP_OK;
        
        fb = esp_camera_fb_get();
        
        if (!fb)
        {
	        Serial.println("Camera capture failed");
          // flash back off
          digitalWrite(4, LOW);
	        return false;
        }
        // should have buf now, kill flash
        digitalWrite(4, LOW);


        if(!uploadFile(timeStringBuff, (unsigned char *)fb->buf, fb->len))
        {
            // flash back off
            digitalWrite(4, LOW);
            return false;
        }
        esp_camera_fb_return(fb);
    }
    // flash back off
    digitalWrite(4, LOW);
    return true;
}
