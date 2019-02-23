void get_sample(){
  //ads1115.setGain(GAIN_SIXTEEN);
  results = abs(ads1115.readADC_Differential_0_1());
int val = map(results,0,32767,0,600);
 c_val = c_val + val;
 last_t = millis();
  k=k-1;
  Serial.print("Got Sample heeee  ");
  Serial.print(results);

  Serial.print("  ==============   ");
  Serial.println(val);
  delay(300);
}
