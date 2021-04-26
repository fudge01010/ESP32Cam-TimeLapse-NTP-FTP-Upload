# ESP32Cam-TimeLapse-NTP-FTP-Upload
Project forked from https://github.com/bitluni/ESP32CamTimeLapse

Add upload to FTP instead of SD and use filenames with date time pattern from NTP server.

Lapse is started automatically after board is powered up.

Roll back original web ui from ESP32Cam example (Without manual lapse settings).

Arduino board setup

```
Board: ESP32 Dev Module
CPU Freq: 240Mhz
Flash Size: 4MB
Partition Scheme Default 4MB with spiffs
PSRAM: Enabled # Is important for UXGA frame size
```
## Convert images to movie

`ffmpeg -r 10 -f image2 -pattern_type glob -i '*.jpg'  -vcodec libx264 -crf 10 -pix_fmt yuvj422p lapse.mp4`

# ESP32CamTimeLapse

Please visit https://bitluni.net/esp32camtimelapse for project information.
