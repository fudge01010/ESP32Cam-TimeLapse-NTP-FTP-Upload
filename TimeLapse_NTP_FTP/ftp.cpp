// FTP Client Lib
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32_FTPClient.h>

bool uploadFile(const char *path, unsigned char *data, unsigned long len)
{
  // FTP Server credentials
  char ftp_server[] = "1.2.3.4";
  char ftp_user[]   = "ftpuser";
  char ftp_pass[]   = "****";

  ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);

  ftp.OpenConnection();

  ftp.InitFile("Type I");
  ftp.ChangeWorkDir("/dir/where/you/save/your/photos/"); // change it to reflect your directory
  const char *f_name = path;
  ftp.NewFile( f_name );
  ftp.WriteData(data, len);
  ftp.CloseFile();
  ftp.CloseConnection();

  return true;
}
