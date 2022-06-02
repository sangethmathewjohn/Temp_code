#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "drip-irigation-8b221-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "4kc0J60267BtPLKjIusnIB465ub6QJIRJ67nl0Te"
#define WIFI_SSID "keylogger"
#define WIFI_PASSWORD "keylogger"

const int Sensor=A0;
const int relay=13;
void setup(){
  Serial.begin(115200);
   pinMode(relay,OUTPUT);
  pinMode(Sensor,INPUT);
   while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
     }

    // connect to wifi.
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

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop(){
   float moisture_percentage;
//
  moisture_percentage = ( 100.00 - ( (analogRead(Sensor)/1023.00) * 100.00 ) );
  Serial.println(moisture_percentage);
    Firebase.setFloat("moisture_percentage",moisture_percentage);
  if (Firebase.failed()) {  
      Serial.print("setting /number failed:");  
      Serial.println(Firebase.error());    
      return;  
  }
  if (moisture_percentage<13){
    digitalWrite(relay,HIGH);
  }
  else{
    digitalWrite(relay,LOW);
  }
}
