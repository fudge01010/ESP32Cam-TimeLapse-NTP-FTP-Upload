# ESP32Cam-TimeLapse-NTP-FTP-Upload
Project forked from https://github.com/Ceda/ESP32Cam-TimeLapse-NTP-FTP-Upload - which is orginally forked from https://github.com/bitluni/ESP32CamTimeLapse

- Uses NTP to get local time, and saves filenames with a sane date+time pattern.
- Uploads files (via FTP) to provided server
- Adjusted camera config settings to use "most recent" image from framebuffer
- Added support for Flash (internal or external).


Lapse is started automatically after board is powered up.


My Arduino Environment settings:

```
Board: ESP32 Dev Module
CPU Freq: 240Mhz
Flash Size: 4MB
Partition Scheme Default 4MB with spiffs
PSRAM: Enabled # Is important for UXGA frame size
```

## Convert images to movie

`ffmpeg -r 10 -f image2 -pattern_type glob -i '*.jpg'  -vcodec libx264 -crf 10 -pix_fmt yuvj422p lapse.mp4`

Adjust `-r 10` for framerate of generated clip. Change `-vcodec libx264` to `libx265` for reduced filesize.


Original project [here](https://bitluni.net/esp32camtimelapse)
