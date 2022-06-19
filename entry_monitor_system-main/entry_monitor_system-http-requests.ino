// #include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include <ArduinoJson.h>
String received_json;

StaticJsonDocument<2000> doc; // Allocates memory on the stack

String payload;

#include "entry_monitor_system-main.h"
const char* rootCACertificate = \ 
"-----BEGIN CERTIFICATE-----\n"\
"MIIFFjCCAv6gAwIBAgIRAJErCErPDBinU/bWLiWnX1owDQYJKoZIhvcNAQELBQAw\n"\
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"\
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMjAwOTA0MDAwMDAw\n"\
"WhcNMjUwOTE1MTYwMDAwWjAyMQswCQYDVQQGEwJVUzEWMBQGA1UEChMNTGV0J3Mg\n"\
"RW5jcnlwdDELMAkGA1UEAxMCUjMwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n"\
"AoIBAQC7AhUozPaglNMPEuyNVZLD+ILxmaZ6QoinXSaqtSu5xUyxr45r+XXIo9cP\n"\
"R5QUVTVXjJ6oojkZ9YI8QqlObvU7wy7bjcCwXPNZOOftz2nwWgsbvsCUJCWH+jdx\n"\
"sxPnHKzhm+/b5DtFUkWWqcFTzjTIUu61ru2P3mBw4qVUq7ZtDpelQDRrK9O8Zutm\n"\
"NHz6a4uPVymZ+DAXXbpyb/uBxa3Shlg9F8fnCbvxK/eG3MHacV3URuPMrSXBiLxg\n"\
"Z3Vms/EY96Jc5lP/Ooi2R6X/ExjqmAl3P51T+c8B5fWmcBcUr2Ok/5mzk53cU6cG\n"\
"/kiFHaFpriV1uxPMUgP17VGhi9sVAgMBAAGjggEIMIIBBDAOBgNVHQ8BAf8EBAMC\n"\
"AYYwHQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMBMBIGA1UdEwEB/wQIMAYB\n"\
"Af8CAQAwHQYDVR0OBBYEFBQusxe3WFbLrlAJQOYfr52LFMLGMB8GA1UdIwQYMBaA\n"\
"FHm0WeZ7tuXkAXOACIjIGlj26ZtuMDIGCCsGAQUFBwEBBCYwJDAiBggrBgEFBQcw\n"\
"AoYWaHR0cDovL3gxLmkubGVuY3Iub3JnLzAnBgNVHR8EIDAeMBygGqAYhhZodHRw\n"\
"Oi8veDEuYy5sZW5jci5vcmcvMCIGA1UdIAQbMBkwCAYGZ4EMAQIBMA0GCysGAQQB\n"\
"gt8TAQEBMA0GCSqGSIb3DQEBCwUAA4ICAQCFyk5HPqP3hUSFvNVneLKYY611TR6W\n"\
"PTNlclQtgaDqw+34IL9fzLdwALduO/ZelN7kIJ+m74uyA+eitRY8kc607TkC53wl\n"\
"ikfmZW4/RvTZ8M6UK+5UzhK8jCdLuMGYL6KvzXGRSgi3yLgjewQtCPkIVz6D2QQz\n"\
"CkcheAmCJ8MqyJu5zlzyZMjAvnnAT45tRAxekrsu94sQ4egdRCnbWSDtY7kh+BIm\n"\
"lJNXoB1lBMEKIq4QDUOXoRgffuDghje1WrG9ML+Hbisq/yFOGwXD9RiX8F6sw6W4\n"\
"avAuvDszue5L3sz85K+EC4Y/wFVDNvZo4TYXao6Z0f+lQKc0t8DQYzk1OXVu8rp2\n"\
"yJMC6alLbBfODALZvYH7n7do1AZls4I9d1P4jnkDrQoxB3UqQ9hVl3LEKQ73xF1O\n"\
"yK5GhDDX8oVfGKF5u+decIsH4YaTw7mP3GFxJSqv3+0lUFJoi5Lc5da149p90Ids\n"\
"hCExroL1+7mryIkXPeFM5TgO9r0rvZaBFOvV2z0gp35Z0+L4WPlbuEjN/lxPFin+\n"\
"HlUjr8gRsI3qfJOQFy/9rKIJR0Y/8Omwt/8oTWgy1mdeHmmjk7j1nYsvC9JSQ6Zv\n"\
"MldlTTKB3zhThV1+XWYp6rjd5JW1zbVWEkLNxE7GJThEUG3szgBVGP7pSWTUTsqX\n"\
"nLRbwHOoq7hHwg==\n"\
"-----END CERTIFICATE-----\n" ;


// To register and get sessionID
// we send a GET request with the form parameters
void httpsGETRegister(String device_name, String user_name,
                       String password, String ip_address, String device_location)
{
    WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    client -> setCACert(rootCACertificate);

    {
      // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
      HTTPClient https;
      //    // ServerName for requesting sessionID / registering
    String serverName = "https://test.profil.app/stamp/register?";
    String serverPath = serverName + "name=" + device_name + "&ip=" + ip_address + "&location=" + device_location +
                        "&username=" + user_name + "&password=" + password;
      Serial.print("[HTTPS] begin...\n");
      if (https.begin(*client, serverPath)) {  // HTTPS
        Serial.print("[HTTPS] GET...\n");
        // start connection and send HTTP header
        int httpCode = https.GET();
        Serial.print("Https code = ");
        Serial.println(httpCode);
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.println(payload);  // Print the data received from the server // Payload is a JSON
            DeserializationError error = deserializeJson(doc, payload);  // Deserialize the JSON document
          // Test if parsing succeeds.
          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            return;
            Serial.println(payload);
          }
          
          String sessionId = doc["message"]["sessionid"];
          Serial.print("Session ID is:");
          Serial.println(sessionId);
          preferences.begin("system", false);
          preferences.putString("sessionId", sessionId);
          Serial.println("SESSION ID STORED...");
          preferences.end();
          
        } else {
          Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
  
        https.end();
      } else {
        Serial.printf("[HTTPS] Unable to connect\n");
      }
      // End extra scoping block
    }
  
    delete client;
 }
 }

}

void httpsGETUsersList()
{
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client)
  {
    client->setCACert(rootCACertificate);

    {
      HTTPClient https;

      // ServerPath for requesting users list
//      String serverPath = "https://" + domain + "/stamp/users?sessionid=" + sessionId;
        String serverPath = "https://test.profil.app/stamp/users?sessionid=" + sessionId;


      https.begin(*client, serverPath.c_str());

      // Send HTTP POST request
      int httpsResponseCode = https.GET();

      String payload = "{}";

      if (httpsResponseCode > 0)
      {
          Serial.print("HTTP Response code: ");
          Serial.println(httpsResponseCode);
        payload = https.getString();
      }
      else
      {
          Serial.print("Error code: ");
          Serial.println(httpsResponseCode);
      }
      // Free resources
      https.end();

      JSONVar myObject = JSON.parse(payload);
      if (isDev)
        Serial.println(JSON.stringify(myObject));

      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined")
      {
        if (isDev)
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
  }
}

// To POST data when RFID tag has been recognized and acceptable
void httpsPOSTHello(String id, String timestamp)
{
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client)
  {
    client->setCACert(rootCACertificate);

    {
      HTTPClient https;

      // ServerName for posting data
      String serverPath = "https://" + domain + "/stamp/hello?sessionid=" + sessionId;
      String data = "&cardid=" + id + "&date=" + timestamp;

      // Your IP address with path or Domain name with URL path
      https.begin(*client, serverPath.c_str());

      // Send HTTP POST request
      int httpsResponseCode = https.POST(data);

        Serial.print("HTTP Response code: ");
        Serial.println(httpsResponseCode);
      // Free resources
      https.end();
    }
  }
}
