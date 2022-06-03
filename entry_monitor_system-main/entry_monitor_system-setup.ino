#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#include "entry_monitor_system-main.h"
#include "entry_monitor_system-http-requests.h"
#include "entry_monitor_system-leds-buzzer.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

bool SETUP_MODE = true;

const char *ssid = "ENTRY MONITOR SYSTEM";
const char *password = "123456789";

const char *PARAM_USERNAME = "user_name";
const char *PARAM_PASSWORD = "password";
const char *PARAM_DOMAIN = "domain";
const char *PARAM_IP = "ip_address";
const char *PARAM_DEVICE = "device_name";
const char *PARAM_LOCATION = "device_location";

void read_saved_data()
{
  preferences.begin("system", false);
  user_name = preferences.getString("user_name", "");
  user_password = preferences.getString("user_password", "");
  sessionId = preferences.getString("sessionId", "");
  device_name = preferences.getString("_name", "");
  device_ip = preferences.getString("ip", "");
  device_location = preferences.getString("device_location", "");
  domain = preferences.getString("domain", "");

  Serial.print("user name is: ");
  Serial.println(user_name);
  Serial.print("sessionId is: ");
  Serial.println(sessionId);
  Serial.print("user_password is: ");
  Serial.println(user_password);
  Serial.print("domain is: ");
  Serial.println(domain);
  Serial.print("ip is: ");
  Serial.println(device_ip);
  Serial.print("d-name is: ");
  Serial.println(device_name);
  Serial.print("location is: ");
  Serial.println(device_location);
  preferences.end();
}

void register_and_save_data()
{
  // ******* After getting the parameters from the web form,
  // ******* we call the register device HTTP request below
  //
  Serial.println("::::::REGISTERING");
  //    httpGETRegister(device_name, user_name, user_password, device_ip, device_location);
  // If sessionId has been set suuccessfuly, we store the device details to Flash
  preferences.begin("system", false);
  preferences.putString("user_name", user_name);
  preferences.putString("user_password", user_password);
  preferences.putString("sessionId", sessionId);
  preferences.putString("_name", device_name);
  preferences.putString("ip", device_ip);
  preferences.putString("device_location", device_location);
  preferences.putString("domain", domain);
  preferences.end();
  Serial.println(":::::: REGISTRATION SUCCESSFUL!");
  Serial.print(">>>>>>>> Saved details!");
  Serial.print("");
  Serial.print("");
  Serial.print(">>>>>>>> Restarting Device");
  //    ESP.restart();
}

const char index_html[] PROGMEM = R"rawliteral(
 <!DOCTYPE HTML>
 <html>
 <head>
 <style type="text/css">
 div{
   background-color: #dddd;
   width: 80%;
   margin: 20px auto;
   border-radius: 5px;
   padding: 10px;
   font-family: Lucida Grande, Microsoft Sans Serif; 
 }
 span{
  font-weight:bold; 
  color: #006633;
  display: flex;
  justify-content: center;
  padding: 10px;
 }
 form{
   padding: 25px;
   display: block;
 }

 input{
   width: 50%; 
   padding: 10px;
   display: block;
 }
 input[type=submit]{
   background-color: #006633;
   border: none;
   color: white;
   text-decoration: none;
   margin: 4px 2px;
   cursor: pointer;
   width: 10%;
 }
 input[type=text],input[type=password]{
   padding: 10px 10px;
   box-sizing: border-box;
 }
 p{
   text-align: center;
   font-style: italic;
    color: #006633;
 }
 </style>
   <title>ENTRY MONITOR REGISTRATION</title>
   <meta name="viewport" content="width=device-width, initial-scale=1">
   </head><body>
   <div>
   <span> ENTRY MONITOR SYSTEM SETUP </span>
   <form action="/get">
     <input type="text" name="user_name" placeholder="User Name"><br>
     <input type="password" name="password" placeholder="Your password.."><br>
     <input type="text" name="domain" placeholder="Domain Name"><br>
     <input type="text" name="ip_address" placeholder="IP Address"><br>
     <input type="text" name="device_name" placeholder="Device Name"><br>
     <input type="text" name="device_location" placeholder="Device Location"><br>
     <input type="submit" value="Submit"><br>
    </form><br>
    <p>
     Thanks for Registering with us &copy; 2022
    </p>
 </div>
 </body>
 </html>)rawliteral";

void setupRegistration()
{
  preferences.begin("system", false);
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  if (SETUP_MODE)
  {
    // Send web page with input fields to client
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send_P(200, "text/html", index_html); });

    // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
     String inputMessage;
     String inputParam;
     // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
       user_name = request->getParam(PARAM_USERNAME)->value().c_str();
       Serial.print("Typed User Name is:");
       Serial.println(user_name);
     
     // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
       user_password = request->getParam(PARAM_PASSWORD)->value();
       Serial.print("Typed Password is:");
       Serial.println(user_password);
     
     // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
       domain = request->getParam(PARAM_DOMAIN)->value();
       Serial.print("Typed Domain Name is:");
       Serial.println(inputMessage);
     
       device_ip = request->getParam(PARAM_IP)->value();
       Serial.print("Typed IP is:");
       Serial.println(device_ip);
     
       device_name = request->getParam(PARAM_DEVICE)->value();
       Serial.print("Typed Device Name is:");
       Serial.println(device_name);
     
       device_location = request->getParam(PARAM_LOCATION)->value();
       Serial.print("Typed Location is:");
       Serial.println(device_location);
       Serial.println("");Serial.println("");

       register_and_save_data();

      //     Serial.println(inputMessage);
     request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                      + inputParam + ") with value: " + inputMessage +
                                      "<br><a href=\"/\">Return to Home Page</a>"); });
    server.begin();
  }
}

void check_device_status()
{
  read_saved_data();
  if (user_name == "" && user_password == "" && device_name == "")
  {
    // shows device is not registered and got not data saved, launch Access point
    Serial.println("No data was found! Launching Access Point ...");
    setupRegistration();
  }
  else if (sessionId == "")
  {
    httpsGETRegister(device_name, user_name, user_password, device_ip, device_location);
    // means registered so go for session ID after connecting to internet via ethernet
  }
  else
  {
    blinkSetupDoneLED(); // Turn on red led to show setup is already done
    Serial.println(":::::: SETUP AND SESSION ID SET!  REACHING FOR ETHERNET...");
  }
}