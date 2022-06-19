#include <WiFi.h>
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12
#include <ETH.h>
static bool eth_connected = false;
#include <Preferences.h>
#include "entry_monitor_system-setup.h"
#include "entry_monitor_system-rfid-reading.h"
#include "entry_monitor_system-leds-buzzer.h"
#include "entry_monitor_system-http-requests.h"
#include "entry_monitor_system-time-n-date.h"
#include "entry_monitor_system_ethernet.h"


// Whether to print serial output
bool isDev = true;

// Preferences instance
Preferences preferences;
String cardid = "acbf38d3-d5af-4f10-a5a6-7c654e968077";
String date_now = "2022-04-19-23-48-12";
// Device details stored after registration
String sessionId = "";
String user_name = "";
String user_password = "";
String device_ip = "";
String device_location = "";
String domain = "test.profil.app";
String device_name = "";
// List to store acceptable user rfids
String userIdsList[] = {};
// This tracks number of acceptable user ids
int numberOfUserIds = 0;

void simulateEthernetConnection()
{
    Serial.print("Connecting to ");
    Serial.println("Homelander....");
    WiFi.onEvent(WiFiEvent);
    ETH.begin();
    if(eth_connected){
    Serial.print("Actively connected to the Internet, getting device UID...");
    Serial.println("Saving deviceUID to flash...");
//    httpsGETRegister(device_name, user_name, user_password, device_ip, device_location);
    } 
}



void setup()
{
    // Initialize serial
    Serial.begin(115200);
    // Initialize led and buzzer pins
    preferences.begin("system", false);
    setupRFID();
    check_device_status();
    simulateEthernetConnection();
    setupLEDSnBuzzer();
    // Turn on green led to show board is in operation
    blinkOperationLED();
    //        httpsGETUsersList(); // send http request to get list of acceptable user ids
//        setupRFID();         // Initialize RFID
    preferences.end();
}

void loop(){
    
    if (eth_connected)
    {
      readRFIDTag(); 
      httpsGETUsersList();
//      httpsPOSTHello(cardid,date_now);
    }else{
      Serial.println("Ethernet not connected!");
    }
}
