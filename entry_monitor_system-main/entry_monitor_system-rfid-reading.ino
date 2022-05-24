// Initialize all the libs needed
#include <SPI.h>
#include <MFRC522.h>
#include "entry_monitor_system-leds-buzzer.h"
#include "entry_monitor_system-http-requests.h"
#include "entry_monitor_system-time-n-date.h"
#include "entry_monitor_system-main.h"

#define SS_PIN 13
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create and instance of the  MFRC522(the name is absolutely random).

void setupRFID()
{
    SPI.begin();        // Initialize SPI bus
    mfrc522.PCD_Init(); // Initialize MFRC522
    Serial.println("Approximate your card to the reader...");
    Serial.println();
}

void read_tag()
{
    // Look for new cards and reset loop if none is present
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }
    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    // Show UID on serial monitor
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();

    bool isIdAcceptable = false;

    // ******** AUTHORIZATION *********
    // Checks if the RFID is acceptable
    for (int i = 0; i < numberOfUserIds; i++)
    {
        // if the rfid is in the list
        if (content.substring(1) == userIdsList[i])
        {
            isIdAcceptable = true;
            break; // break the loop
        }
    }

    if (isIdAcceptable)
    {
        String timeStamp = getDateTime();               // get date and time
        httpPOSTHello(content.substring(1), timeStamp); // send hello request

        Serial.println("Authorized access");
        Serial.println();

        blinkLEDnBuzz(1); // blink entry led and sound buzzer
        // blinkLEDnBuzz(2); // blink exit led and sound buzzer
    }
    else
    {
        Serial.println(" Access denied");
        blinkLEDnBuzz(3); // blink access denied led
    }
}
