#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// Replace with your network credentials
const char* ssid     = "THE DEVELOPER";
const char* password = "MANAGEMENT2";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
