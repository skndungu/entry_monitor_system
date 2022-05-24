// #include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "entry_monitor_system-main.h"


//
//
// To register and get sessionID
// we send a GET request with the form parameters
void httpGETRegister(String device_name, String user_name,
                       String password, String ip_address, String location)
{

    HTTPClient http;

    // ServerName for requesting sessionID / registering
    String serverName = "https://test.profil.app/stamp/register?";
    String serverPath = serverName + "name=" + device_name + "&ip=" + ip_address + "&location=" + location +
                        "&username=" + user_name + "&password=" + password;

    // Your IP address with path or Domain name with URL path
    http.begin(serverPath.c_str());

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String _sessionId = "";
    String payload = "{}";

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
        Serial.print(payload);
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    JSONVar myObject = JSON.parse(payload);

    // JSON.typeof(jsonVar) can be used to get the type of the var
    if (JSON.typeof(myObject) == "undefined")
    {
        Serial.println("Parsing input failed!");
        // return;
    }

    // myObject.keys() can be used to get an array of all the keys in the object
    JSONVar keys = myObject.keys();

    JSONVar value = myObject[keys[0]];
    Serial.print("sessionId");
    Serial.print(" = ");
    Serial.println(value);
    // We set 
    sessionId = value;
    Serial.print(sessionId);
}


//
//
// To get a list of acceptable user RFIDS
void httpGETUsersList()
{
    HTTPClient http;

    // ServerPath for requesting users list
    String serverPath = "https://test.profil.app/stamp/users?sessionid=" + sessionId;

    http.begin(serverPath.c_str());

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payload = "{}";

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    JSONVar myObject = JSON.parse(payload);
    Serial.println(JSON.stringify(myObject));

    // JSON.typeof(jsonVar) can be used to get the type of the var
    if (JSON.typeof(myObject) == "undefined")
    {
        Serial.println("Parsing input failed!");
        return;
    }

    // myObject.keys() can be used to get an array of all the keys in the object
    JSONVar keys = myObject.keys();
    
    numberOfUserIds = keys.length();

    // add each object value to the user ids list
    for (int i = 0; i < keys.length(); i++)
    {
        JSONVar value = myObject[keys[i]];
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.println(value);
        userIdsList[i] = JSON.stringify(value);
    }
}


//
//
// To POST data when RFID tag has been recognized and acceptable
void httpPOSTHello(String id, String timestamp)
{
    HTTPClient http;

    // ServerName for posting data
    String serverName = "https://test.profil.app/stamp/hello?sessionid=" + sessionId;
    String data = "&cardid=" + id + "&date=" + timestamp;

    // Your IP address with path or Domain name with URL path
    http.begin(serverName.c_str());

    // Send HTTP POST request
    int httpResponseCode = http.POST(data);

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    // Free resources
    http.end();
}

