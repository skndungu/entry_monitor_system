  #include <Arduino.h>
  #ifdef ESP32
 #include <WiFi.h>
 #include <AsyncTCP.h>
  #else
    #include <ESP8266WiFi.h>
    #include <ESPAsyncTCP.h>
  #endif
 #include <ESPAsyncWebServer.h>
 #include "entry_monitor_system-http-requests.h"
 #include "entry_monitor_system-main.h"

 AsyncWebServer server(80);

// // REPLACE WITH YOUR NETWORK CREDENTIALS
 const char *ssid = "THE DEVELOPER";
 const char *password = "123456789";

 const char *PARAM_USERNAME = "user_name";
 const char *PARAM_PASSWORD = "password";
 const char *PARAM_DOMAIN = "domain";
 const char *PARAM_IP = "ip_address";
 const char *PARAM_DEVICE = "device_name";
 const char *PARAM_LOCATION = "device_location";

 // HTML web page to handle 3 input fields (input1, input2, input3)
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
   display: flex;
  justify-content: center;

 }

 input{
   width: 50%; 
   padding: 10px;
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
   <title>ESP Input Form</title>
   <meta name="viewport" content="width=device-width, initial-scale=1">
   </head><body>
   <div>
   <span> ENTRY MONITOR SYSTEM SETUP </span>
   <form action="/get">
     <input type="text" name="user_name" placeholder="User Name">
     <input type="submit" value="Submit">
   </form><br>
   <form action="/get">
     <input type="password" name="password" placeholder="Your password..">
     <input type="submit" value="Submit">
   </form><br>
     <form action="/get">
     <input type="text" name="domain" placeholder="Domain Name">
     <input type="submit" value="Submit">
   </form><br>
   <form action="/get">
     <input type="text" name="ip_address" placeholder="IP Address">
     <input type="submit" value="Submit">
   </form><br>
     <form action="/get">
     <input type="text" name="device_name" placeholder="Device Name">
     <input type="submit" value="Submit">
   </form><br>
     <form action="/get">
     <input type="text" name="device_loaction" placeholder="Device Location">
     <input type="submit" value="Submit">
   </form><br>
     <p>
     Thanks for Registering with us &copy; 2022
 </p>
 </div>
 </body>
 </html>)rawliteral";
 

//   // Send web page with input fields to client
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send_P(200, "text/html", index_html); });

//   // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
   server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
             {
     String inputMessage;
     String inputParam;
     // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
     if (request->hasParam(PARAM_USERNAME)) {
       inputMessage = request->getParam(PARAM_USERNAME)->value();
       inputParam = PARAM_USERNAME;
     }
     // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
     else if (request->hasParam(PARAM_PASSWORD)) {
       inputMessage = request->getParam(PARAM_PASSWORD)->value();
       inputParam = PARAM_PASSWORD;
     }
     // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
     else if (request->hasParam(PARAM_DOMAIN)) {
       inputMessage = request->getParam(PARAM_DOMAIN)->value();
       inputParam = PARAM_DOMAIN;
     }
     else {
       inputMessage = "No message sent";
       inputParam = "none";
     }
     Serial.println(inputMessage);
     request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                      + inputParam + ") with value: " + inputMessage +
                                      "<br><a href=\"/\">Return to Home Page</a>"); });
   server.begin();
  
}

  
   // ******* After getting the parameters from the web form,
   // ******* we call the register device HTTP request below
   //


   // // Create the web server to get registration details
 void setupRegistration(){
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   if (WiFi.waitForConnectResult() != WL_CONNECTED)
   {
     Serial.println("WiFi Failed!");
     return;
   }
   Serial.println();
   Serial.print("IP Address: ");
   Serial.println(WiFi.localIP());

   Serial.println("::::::::::::::::::::::::: REGISTERING");
   httpGETRegister("DEV1999", "Mo", "123456", "198.168.48.1", "Mombasa");
   // If sessionId has been set suuccessfuly, we store the device details to Flash
   if (sessionId != "")
   {
     preferences.begin("system", false);
     preferences.putString("sessionId", sessionId);
     preferences.putString("name", PARAM_DEVICE);
     preferences.putString("ip", PARAM_IP);
     preferences.putString("location", PARAM_LOCATION);
     preferences.end();
     Serial.println("::::::::::::::::::::::::: REGISTRATION SUCCESSFUL!");
   }
 }
