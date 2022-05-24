#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setupDateTime()
{
    // Initialize a NTPClient to get time
    timeClient.begin();
    // Set offset time in seconds to adjust for your timezone, for example:
    // GMT +1 = 3600
    // GMT +8 = 28800
    // GMT -1 = -3600
    // GMT 0 = 0
    timeClient.setTimeOffset(10800); // sets GMT+3hrs
}

// Get timestamp
String getDateTime()
{
    while (!timeClient.update())
    {
        timeClient.forceUpdate();
    }
    // The formattedDate comes with the following format:
    // 2018-05-28T16:00:13Z
    // We need to extract date and time
    String formattedDate = timeClient.getFormattedDate();
    Serial.println(formattedDate);

    int splitT = formattedDate.indexOf("T");
    String timeStamp = formattedDate.substring(0, splitT) + String("-") + formattedDate.substring(splitT + 1, formattedDate.length() - 1);
    Serial.print("Timestamp is: ");
    Serial.println(timeStamp);

    return timeStamp;
}
