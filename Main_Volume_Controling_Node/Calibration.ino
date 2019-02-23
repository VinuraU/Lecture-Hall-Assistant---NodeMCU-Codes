void calibrate(){

   HTTPClient http;  //Object of class HTTPClient
    http.begin("http://192.168.43.165/ele/public/audio/reference/set");
    int httpCode = http.GET();
    http.end();   //Close connection

    Serial.println("Calibrated..............................................................................");
    
}
