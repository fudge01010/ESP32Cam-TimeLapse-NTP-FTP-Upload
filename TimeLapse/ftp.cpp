// FTP Client Lib
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32_FTPClient.h>

bool uploadFile(const char *path, unsigned char *data, unsigned long len)
{
  // FTP Server credentials
  char ftp_server[] = "changeMe";
  char ftp_user[]   = "changeMe";
  char ftp_pass[]   = "changeMe";

  ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);

  ftp.OpenConnection();

  ftp.InitFile("Type I");
  ftp.ChangeWorkDir("/webcam/"); // change it to reflect your directory
  const char *f_name = path;
  ftp.NewFile( f_name );
  ftp.WriteData(data, len);
  ftp.CloseFile();
  ftp.CloseConnection();

  return true;
}
