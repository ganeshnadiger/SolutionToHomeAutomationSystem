#include <Servo.h>
#define SS_PIN 4  //D2
#define RST_PIN 5 //D1
#define Relay_Motor 0 //D3 for servo motor
#define Relay_Motor2 02 //D4 for servo motor

#include <SPI.h>
#include <MFRC522.h>

Servo s1;
Servo s2;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //pinMode(Relay_Motor,OUTPUT);
  s1.attach(Relay_Motor);
  s2.attach(Relay_Motor2);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  int pos;
  if (content.substring(1) == "56 99 5E 1F") //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    Serial.println(" IOT GROUP!!! ");
    delay(1000);
    Serial.println(" Have FUN ");
    Serial.println();
    for (pos = 02; pos <= 95; pos += 1) { 
    s1.write(pos); 
    delay(20);
    }
    for (pos =95; pos >= 02; pos -= 1) { 
    s2.write(pos); 
    delay(20);
    }
    delay(10000);
    for (pos = 95; pos >= 02; pos -= 1) {
      s1.write(pos);
      delay(20);
      }
      for (pos = 02; pos <= 95; pos += 1) {
      s2.write(pos);
      delay(20);
      }
      statuss = 1;
      //digitalWrite(Relay_Motor,HIGH);
  }
  
  else   {
     //digitalWrite(Relay_Motor,LOW);
   Serial.println(" Access Denied ");
   Serial.println(" TRY AGAIN!!! ");
    delay(3000);
    
  }
} 
