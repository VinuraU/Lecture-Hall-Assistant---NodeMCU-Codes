void get_values(){
 if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://192.168.43.165/ele/public/controllers/get/123");   // Calling API get/ 'Device ID'
   
    int httpCode = http.GET();
    Serial.println(httpCode);
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      Serial.println(payload);
//My add
//-----------------------------------------------------------------------------------------------------
const size_t bufferSize = JSON_OBJECT_SIZE(3) + 30;
DynamicJsonBuffer jsonBuffer(bufferSize);

//const char* json = "{\"status\":200,\"data\":35,\"errors\":\"\"}";

JsonObject& root = jsonBuffer.parseObject(payload);


int status_1 = root["status"]; // 200
int data = root["data"]; // 35
const char* errors = root["errors"]; // ""
n_value = data;
Serial.println("REceived/.....");
Serial.println(data);

 //-----------------------------------------------------------------------------------------------------------------     
      // TODO: Parsing
    }
    
    http.end();   //Close connection
  }
  
}

