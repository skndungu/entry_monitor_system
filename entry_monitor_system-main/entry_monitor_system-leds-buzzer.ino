#include <Arduino.h>
#include <Preferences.h>

const byte led_enter = 36;        // green
const byte led_leave = 39;        // yellow
const byte led_unrecognized = 34; // red
const byte led_in_operation = 35; // green
const byte led_setup_done = 32;   // red
const byte buzzer = 33;

void setupLEDSnBuzzer()
{
    // Set up pins
    pinMode(led_enter, OUTPUT);
    pinMode(led_leave, OUTPUT);
    pinMode(led_unrecognized, OUTPUT);
    pinMode(led_setup_done, OUTPUT);
    pinMode(led_in_operation, OUTPUT);
    pinMode(buzzer, OUTPUT);
}

// Blink respective LED
void blinkLEDnBuzz(int led)
{
    switch (led)
    {
    case 1: // User has entered
        Serial.print("Entry in process...");
        digitalWrite(led_enter, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(led_enter, LOW);
        digitalWrite(buzzer, LOW);
        break;
    case 2: // User has exited
        Serial.print("Exit in processs...");
        digitalWrite(led_enter, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(led_enter, LOW);
        digitalWrite(buzzer, LOW);
        break;
    case 3: // User denied access
        Serial.print("Access denied or Card not recognized!");
        digitalWrite(led_enter, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(led_enter, LOW);
        digitalWrite(buzzer, LOW);
        break;

    default:
        break;
    }
}

void blinkSetupDoneLED()
{
    digitalWrite(led_setup_done, HIGH);
}

void blinkOperationLED()
{
    digitalWrite(led_in_operation, HIGH);
}