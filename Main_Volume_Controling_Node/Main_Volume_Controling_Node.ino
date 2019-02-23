 //Wi-Fi Connectivity
 //-----------------------------------------------------------------------------------------------------------
 #include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "Lecture Hall Assistant Network";
const char* password = "12345678";



 
 
 //================================================================================================================
 
 //Volume Controlling Section
 //--------------------------------------------------------------------------------------------------------------------------------
 #define UD D3
#define INC D2 
#define CS D1
#define up_LED D8
#define down_LED D0

#define mic_in A0    //Detect Voice

#define amp D4     //Amp enable pin
#define Buzzer D5  //Buzzer pin 
#define discharge D6   //Discharge audio detection capacitor
#define conct D7      //Connected LED


//SET VALUES
//---------------------------------------------------------------------------------------------------------------------------------
int target_value = 70;  // needed sound level
int upb = 80;      // Maximum capable volume for the hall
int block = 7;   // change per command
int f_block = 3;   //fine change per cmd

int fine = 10;  // Margin  for fine tune
int clr_t = 5000;  // Time duration to discharge capacitor
int min_l = 2;   // Minimum volume of the lecturer                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

int n_value = 0;   //New sound level from API
int c_vol = 0;    //Current Volume
int t_clr = 0 ;   // Start counting for capacitor discharging


//Flags
//----------------------------------------------------------------------------------------------------------------------------------

bool need_corrected = false;     //Whether volume is adjusted
unsigned long timer_count = 0;  
unsigned long t_calibrate =0; 
bool counting_silence = false;   
bool com_test = false; 
bool calibration= false; 
bool allowed_cal = true;

int exp_time = 60000;   //Expiring Time of Calibrated sound level   
int silent_time = 5000;   //Detect silence to recalibrate 
int chnge = block;   //Current changing amount of volume

//-----------------------------------------------------------------------------------------------------------------------------------



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
  





  //==============================================================================================================================

  
  // For Volume controller
 //----------------------------------------------------------------------------------------------------------------------------------
  // CS LOW is active
 pinMode(CS, OUTPUT);
  digitalWrite(CS, LOW); // ON

  // INC - LOW is active
  pinMode(INC, OUTPUT);
  digitalWrite(INC, HIGH); // OFF

  // UP is high, DOWN is low
  pinMode(UD, OUTPUT); 

  
//------------------------------------------------------------------------------------------------------------------------------------
pinMode(mic_in,INPUT);
pinMode(amp,OUTPUT);
pinMode(Buzzer,OUTPUT);
pinMode(discharge,OUTPUT);
digitalWrite(amp,0);
digitalWrite(discharge,0);

pinMode(down_LED,OUTPUT);
pinMode(up_LED,OUTPUT);


digitalWrite(down_LED,1);
digitalWrite(up_LED,1);


t_clr = millis();    //take starting time


//Set initial volume zero
//============================================================================================================
int f = 100;
while(f > 0){
  decrease();
  f = f-1;
}



}

void loop() {


Serial.println(analogRead(mic_in));
      delay(300);


//Discharging
//--------------------------------------------------------------------------------------------------------------------------------
 if ( (millis() - t_clr) > clr_t){
  Serial.print("Mic In======== ");
  Serial.println(analogRead(mic_in));
  delay(800);
  digitalWrite(discharge,1);
  delay(20);
  digitalWrite(discharge,0);
  t_clr = millis();
  Serial.println("Discharged///////////");
  
Serial.print("Discharged value          ======== ");
  Serial.println(analogRead(mic_in));
  delay(800);  
}


//Calibration
//==============================================================================================================================

if (com_test == true){
  connected_LED();
Serial.println("YehCom_OK");

//Expiring calibration

   if((millis() - t_calibrate) > exp_time){
      calibration = false; 
     }

 //Execute calibration
    if(calibration == false and allowed_cal == true){
      calibrate();   //Do Calibration
      t_calibrate = millis();       //Take new calibrated time
      
      Serial.print("Calibrated time =  ");
      allowed_cal = false;
      
      calibration = true;
      Serial.println(t_calibrate);
 }
      

//Detect Voice and turn on amp adjust volume
//===========================================================================================================================

if (analogRead(mic_in) > min_l){  
    
    counting_silence = false;   //allow to redetect silence
     allowed_cal = false;
    
    digitalWrite(amp,0);     // turn on the amp
    Serial.println("AMP on");
    delay(111);

  //  n_value =       ;  // Relative audio Value from API
     get_values();
    adjust_vol();
}


//Detect Silence
//----------------------------------------------------------------------------------------------------------------------------

//Start counting silence
if (analogRead(mic_in) < min_l and allowed_cal == false and counting_silence == false){
  timer_count=millis();
  counting_silence = true;
  
      Serial.print("Silent time ========  ");
      Serial.println(timer_count);
      
  }

  //Action for silence
 if((millis()- timer_count) > silent_time and analogRead(mic_in) < min_l and counting_silence == true ){
  allowed_cal = true;
   Serial.print(timer_count);
  Serial.println("  ***************Timed out");
 digitalWrite(amp,HIGH);   // Switch off pre-amp avoiding feedbacks
  }

//-------------------------------------------------------------------------------------------------------------------------------

}
}
