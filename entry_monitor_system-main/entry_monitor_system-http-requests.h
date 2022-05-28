#include <Arduino.h>

void httpPOSTHello(String id, String timestamp);
void httpGETUsersList();
void httpGETRegister(String device_name, String user_name, String password,
                       String ip_address, String device_location);
