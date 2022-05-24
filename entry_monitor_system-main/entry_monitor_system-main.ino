#include <WiFi.h>
#include <Preferences.h>
// #include "entry_monitor_system-setup.h"
#include "entry_monitor_system-rfid-reading.h"
#include "entry_monitor_system-leds-buzzer.h"
#include "entry_monitor_system-http-requests.h"
#include "entry_monitor_system-time-n-date.h"

// Preferences instance
Preferences preferences;

// Device details stored after registration
String sessionId = "";
String name = "";
String ip = "";
String location = "";
// List to store acceptable user rfids
String userIdsList[] = {};
// This tracks number of acceptable user ids
int numberOfUserIds = 0;

void simulateEthernetConnection()
{
  Serial.print("Connecting to ");
  Serial.println("Homelander");
  WiFi.begin("Homelander", "passcode");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void testFuctions()
{
  String time = "";
  delay(3000);
  Serial.println("::::::::::::::::::::::::: REGISTER");
  httpGETRegister("DEV1999", "Mo", "123456", "198.168.48.1", "Mombasa");
  time = getDateTime();
  delay(3000);
  Serial.println("::::::::::::::::::::::::: GET USER LIST");
  time = getDateTime();
  httpGETUsersList();
  delay(3000);
  Serial.println("::::::::::::::::::::::::: POST DATA");
  time = getDateTime();
  httpPOSTHello("3d f5 tg 5a", time);
}

void setup()
{
  // Initialize serial
  Serial.begin(9600);

  // --------------------------------------------------------------------
  // For testing the functions, use WIFI as source of internet connection
  simulateEthernetConnection();
  // --------------------------------------------------------------------

  // Initialize led and buzzer pins
  setupLEDSnBuzzer();
  // Initialize RFID
  setupRFID();
  // Turn on green led to show board is in operation
  blinkOperationLED();

  // Check if sessionId is already defined
  preferences.begin("system", false);
  sessionId = preferences.getString("sessionId", "");

  // If there is a sessionId already defined
  if (sessionId != "")
  {
    blinkSetupDoneLED(); // Turn on red led to show setup is already done
    name = preferences.getString("name", "");
    ip = preferences.getString("ip", "");
    location = preferences.getString("location", "");
    preferences.end();
    httpGETUsersList(); // send http request to get list of acceptable user ids
  }

  // Go to setup if sessionId is not defined
  else
  {
    // Uncomment to test http requests
    // testFuctions();
//    setupRegistration();
  }
}

void loop()
{
  if (sessionId != "")
  {
    read_tag();
  }
}
