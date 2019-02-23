 //Wi-Fi Connectivity
 //-----------------------------------------------------------------------------------------------------------
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define relay D5

// WiFi Parameters
const char* ssid = "Lecture Hall Assistant Network";
const char* password = "12345678";
//================================================================================================================

int n_value = 0; // Current state of the device

void setup() {
pinMode(relay,OUTPUT);
  //Wi-Fi Communication
  //=============================================================================================================================
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.print("My IP Address:  ");
  Serial.print(WiFi.localIP());
  Serial.println("  ");





  //==============================================================================================================================
}

void loop() {
get_values();

if (n_value == 1){
  digitalWrite(relay,1);
  Serial.println ("On");
  
}
 else if (n_value == 0 ){
  digitalWrite(relay,0);
 }
delay(500);
}
