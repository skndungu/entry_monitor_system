#include <WiFi.h>
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT
#define ETH_PHY_POWER 12
#include <ETH.h>
static bool eth_connected = false;
#include <Preferences.h>
#include <Ticker.h>
#include "entry_monitor_system-setup.h"
#include "entry_monitor_system-rfid-reading.h"
#include "entry_monitor_system-leds-buzzer.h"
#include "entry_monitor_system-http-requests.h"
#include "entry_monitor_system-time-n-date.h"
#include "entry_monitor_system_ethernet.h"

// Whether to print serial output
bool isDev = true;

Ticker updater;

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
int savedNumberOfUserIds = 0;

void simulateEthernetConnection()
{
    Serial.print("Connecting to ");
    Serial.println("Homelander....");
    WiFi.onEvent(WiFiEvent);
    ETH.begin();
    if (eth_connected)
    {
        Serial.print("Actively connected to the Internet, getting device UID...");
        Serial.println("Saving deviceUID to flash...");
        //    httpsGETRegister(device_name, user_name, user_password, device_ip, device_location);
    }
}

void getSavedIds()
{
    preferences.begin("system", false);
    for (int i = 0; i < savedNumberOfUserIds; i++)
    {
        // (i+1) because we never saved an id to key "0"
        String idKey = String(i);
        // get each id from it's assigned number
        String id = preferences.getString(idKey.c_str(), "");
        userIdsList[i] = id;
        Serial.println(userIdsList[i]);
    }
    preferences.end();
    Serial.println("Gotten ids stored in flash...");
}

void setup()
{
    // Initialize serial
    Serial.begin(115200);
    // Initialize led and buzzer pins
    preferences.begin("system", false);
    savedNumberOfUserIds = preferences.getInt("savedNumberOfUserIds", 0);
    setupRFID();
    check_device_status();
    simulateEthernetConnection();
    setupLEDSnBuzzer();
    // Turn on green led to show board is in operation
    blinkOperationLED();
    // get user ids from Flash
    //getSavedIds();
    //setupRFID();    
    preferences.end();

}

void loop(){
    if (eth_connected)
    {
        readRFIDTag();
        httpsGETUsersList();
        httpsPOSTHello(cardid, date_now);
     // This ticker will update user id list every 5 minutes
        updater.attach_ms(5000, httpsGETUsersList);
    }
}
