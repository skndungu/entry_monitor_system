#include <Arduino.h>

void httpsPOSTHello(String id, String timestamp);
void httpsGETUsersList();
void httpsGETRegister(String device_name, String user_name, String password,
                       String ip_address, String device_location);
