#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads1115(0x49);  


 //Wi-Fi Connectivity
 //-----------------------------------------------------------------------------------------------------------
 #include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define conct D7



// WiFi Parameters
const char* ssid = "SLT_4G";
const char* password = "12345678";

int last_t;
int c_val=0;
int final_val;
int time_dif=100;
int samples = 10;   //No of samples needed
int k = samples; 
bool com_test = false; 

int16_t results;   //Take I2C Val

void setup() {

  pinMode(conct,OUTPUT);
  digitalWrite(conct,0);

  //Wi-Fi Communication
  //=============================================================================================================================
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
    connecting_LED();
  }

  Serial.print("My IP Address:  ");
  Serial.print(WiFi.localIP());
com_test = true;
connected_LED();

  
 
 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
 ads1115.begin();  // Initialize ads1115
get_sample();
 }

void loop()
{ while(k>0){
  if ((millis() - last_t)>= time_dif){
  get_sample();
 
}
}
finalize();
 



  
//  Serial.print("Differential: "); Serial.print(results); Serial.print("("); Serial.print(results * 3); Serial.println("mV)");
// Serial.println(results);
//  delay(400); 
}
