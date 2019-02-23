void adjust_vol(){
int my = abs(n_value - target_value);
Serial.print("ABS Value ::::");
Serial.println(my);

Serial.print("Current Volume :----------");
Serial.println(c_vol);
if(my < fine  ){           //Fine tuning area
 chnge = f_block ;
}
else {
  chnge = block;   //Normal change
}

Serial.print("New Block value : ******************* ");
Serial.println(chnge);

//Check levels
//============================================================================================================
if (my < 3){
  need_corrected = false;
}
else {
  need_corrected = true;
}
Serial.print("NEeeed Correction ................. ===============  ");
Serial.println(need_corrected);
 //Decrease Volume
 //==============================================================================================================
 
  if (n_value > target_value and need_corrected == true ){
   int k = chnge;
    while(k > 0){
      decrease();
      k = k-1;
      c_vol = c_vol - 1;
    }
    
  }

//Increase Volume
//===============================================================================================================
    if (n_value < target_value and c_vol < upb and need_corrected == true){
   int k =chnge;
    while(k > 0){
      increase();
      k = k-1;
      c_vol = c_vol + 1;
    }
    
  }


  //Alert over volume
  //=============================================================================================================
  
  else if(c_vol == upb or c_vol > upb){
  Serial.println("Over: ");
   digitalWrite(Buzzer,1);
    delay(100);
    digitalWrite(Buzzer,0);
    delay(50);
    digitalWrite(Buzzer,1);
    delay(500);
    digitalWrite(Buzzer,0);

     digitalWrite(Buzzer,1);
    delay(100);
    digitalWrite(Buzzer,0);
    delay(50);
    digitalWrite(Buzzer,1);
    delay(500);
    digitalWrite(Buzzer,0);

    calibrate();
    delay(5000);

     digitalWrite(Buzzer,1);
    delay(600);
    digitalWrite(Buzzer,0);
    delay(50);
    digitalWrite(Buzzer,1);
    delay(100);
    digitalWrite(Buzzer,0);
delay(2000);
digitalWrite(amp,1); //off the amp
delay(500);
    calibrate();
    digitalWrite(amp,0);  //again on the amp
  }

}
