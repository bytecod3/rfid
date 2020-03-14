#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#define granted 2
#define denied 3

byte readCard[4];
String TagID = "5B82BF1B";  // REPLACE this Tag ID with your Tag ID!!!
String CardID = "396CB374";
String tagID = "";


// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() 
{
  // Initiating
  SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
  Serial.begin(9600);
  pinMode(granted, OUTPUT);
  pinMode(denied, OUTPUT);

}

void loop() 
{
  
  //Wait until new tag is available
  while (getID()) 
  {
   
    
    if (tagID == TagID || tagID == CardID ) 
    {

      
      
      Serial.print(" Access Granted!");
      // You can write any code here like opening doors, switching on a relay, lighting up an LED, or anything else you can think of.
      digitalWrite(denied, LOW);
      
      digitalWrite(granted, HIGH);
      delay(500);
      digitalWrite(granted, LOW);
      
      
    }
    else
    {
      Serial.print(" Access Denied!");
      digitalWrite(denied, HIGH);
      delay(500);
      digitalWrite(denied, LOW);
      digitalWrite(granted, LOW);
    }
    
      
      Serial.print(" ID : ");
      Serial.print(tagID);
      
    //delay(2000);

  
  }
}

//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}
