float getDirtVal(){
  digitalWrite(DIRT_SENSOR_LED,LOW); // power on the LED
  delayMicroseconds(300);
  float a = analogRead(DIRT_SENSOR_SEN); // read the dust value
  delayMicroseconds(50);
  return a;
}

float getSonarVal(int num){
  float distance = 0;
  switch(num){
    case 1:
      // Set up trigger
      digitalWrite(SONAR1_TRIG,LOW);
      delayMicroseconds(5);
      // Start Measurement
      digitalWrite(SONAR1_TRIG,HIGH);
      delayMicroseconds(10);
      digitalWrite(SONAR1_TRIG,LOW);
      // Acquire and convert to mtrs
      distance=pulseIn(SONAR1_ECHO,HIGH);
      return (distance*0.01657);
      break;
    case 2:
      // Set up trigger
      digitalWrite(SONAR2_TRIG,LOW);
      delayMicroseconds(5);
      // Start Measurement
      digitalWrite(SONAR2_TRIG,HIGH);
      delayMicroseconds(10);
      digitalWrite(SONAR2_TRIG,LOW);
      // Acquire and convert to mtrs
      distance=pulseIn(SONAR2_ECHO,HIGH);
      return (distance*0.01657);
      break;
    case 3:
      // Set up trigger
      digitalWrite(SONAR3_TRIG,LOW);
      delayMicroseconds(5);
      // Start Measurement
      digitalWrite(SONAR3_TRIG,HIGH);
      delayMicroseconds(10);
      digitalWrite(SONAR3_TRIG,LOW);
      // Acquire and convert to mtrs
      distance=pulseIn(SONAR3_ECHO,HIGH);
      return (distance*0.01657);
      break;
  }
  
}
