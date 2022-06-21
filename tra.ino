#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

const int sensor_pin = A0; 
const int relay= 13;  //pin D7 in nodemcu
const int timer= 14; // pin D6 in nodemcu
#define FIREBASE_HOST "drip-irrigation-3d00d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "l0q7DJajZssTqecTPQ0DxQbKq1Vw8tVEzwLRMAGO"
#define WIFI_SSID "keylogger"
#define WIFI_PASSWORD "keylogger"

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init();
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);//
}

void loop() {
  int t,f;
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
     if(tag=="9917914649"||tag=="29250658"){
      Serial.println("track 1");
      t=1;
      Firebase.setInt("Train1/Track",1);
    }
    else{
      Serial.println("Track 2");
      t=2;
      Firebase.setInt("Train1/Track",2);
    }
    f=Firebase.getInt("Train2/Track");
    Serial.println(f);
    if (t==f){
    Firebase.setString("Track","same");
    }
    else{
    Firebase.setString("Track","diff");
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
   
  }
}
