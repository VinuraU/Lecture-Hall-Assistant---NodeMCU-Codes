void increase(){
  Serial.println("Increasing");
  digitalWrite(CS,1);
  delay(5);
  
  
  digitalWrite(CS,0);
  delay(2);
  
  digitalWrite(UD,1);
  delay(1);
  digitalWrite(INC,1);
  delay(1);
  digitalWrite(INC,0);
  delay(1);
  digitalWrite(INC,1);
  digitalWrite(CS,1);
  delay(1);
  digitalWrite(down_LED,0);
  delay(60);
  digitalWrite(down_LED,1);
}

void decrease(){
  Serial.println("Decreasing");
   digitalWrite(CS,1);
  delay(2);
  
  
  digitalWrite(CS,0);
  delay(2);
  
  digitalWrite(UD,0);
  delay(1);
  digitalWrite(INC,1);
  delay(1);
  digitalWrite(INC,0);
  delay(2);
  digitalWrite(INC,1);
  digitalWrite(CS,1);
  delay(5);

  digitalWrite(down_LED,0);
  delay(60);
  digitalWrite(down_LED,1);
}
