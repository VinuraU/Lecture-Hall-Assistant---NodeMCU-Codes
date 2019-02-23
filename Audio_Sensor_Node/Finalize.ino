void finalize(){

  final_val = c_val / samples;
  c_val = 0;
 k =samples;
  Serial.print("Value = = = ");
  Serial.println(final_val);


  //Upload values

    HTTPClient http;  //Object of class HTTPClient
    String url = "http://192.168.43.165/ele/public/audio/set/2/";
    url+= final_val;
//    Serial.println(url);
//    delay(400);
    http.begin(url);
    int httpCode = http.GET();
    http.end();   //Close connection
  
 
}
