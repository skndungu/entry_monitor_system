// Initialize all the libs needed 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 13
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create and instance of the  MFRC522(the name is absolutely random).

void setup() {
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin(); // Initialize SPI bus
  mfrc522.PCD_Init(); // Initialize MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop() {
read_tag(); 
}

void read_tag(){
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

 // ******** AUTHORIZATION *********
 //change here the UID "BD 31 15 2B" of the card/cards that you want to give access
//  if (content.substring(1) == "BD 31 15 2B"){
//    digitalWrite(trigger1, HIGH);
//    Serial.println("Authorized access");
//    Serial.println();
//    delay(3000);
//  }else{
//    Serial.println(" Access denied");
//    delay(3000);
//  }
}
