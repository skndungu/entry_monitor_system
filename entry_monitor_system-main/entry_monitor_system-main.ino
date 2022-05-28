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


// Preferences instance
Preferences preferences;

// Device details stored after registration
String sessionId = "";
String user_name = "";
String user_password = "";
String device_ip = "";
String device_location = "";
String domain = "";
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
        if (eth_connected) {
    Serial.print("Actively connected to the Internet, getting device UID...");
    Serial.println("Saving deviceUID to flash...");
    httpGETRegister(device_name, user_name, user_password, device_ip, device_location);
    } 
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
    Serial.begin(115200);
    // Initialize led and buzzer pins
    preferences.begin("system", false);
    preferences.end();
    preferences.begin("system", false);
    read_saved_data();
    simulateEthernetConnection();
//    check_device_status();
    setupLEDSnBuzzer();
    // Turn on green led to show board is in operation
    blinkOperationLED();
    
    // Check if sessionId is already defined
    // If there is a sessionId already defined
//    if (sessionId != "")
//    {
//        Serial.println("");Serial.println("");
//        Serial.println(":::::: SETUP ALREADY DONE");
//        read_saved_data();
//        simulateEthernetConnection();
//        blinkSetupDoneLED(); // Turn on red led to show setup is already done
////        httpGETUsersList(); // send http request to get list of acceptable user ids
//        // Initialize RFID
//        setupRFID();
//    }
//
//    // Go to setup if sessionId is not defined
//    else
//    {
//        Serial.println("");Serial.println("");
//        Serial.println(":::::: INITIATING SETUP");
//        // testFuctions();
//        setupRegistration();
//    }
}

void loop()
{
    if (eth_connected)
    {
       httpGETRegister(device_name, user_name, user_password, device_ip, device_location);
    }
}
