float getDirtVal(){
  digitalWrite(DIRT_SENSOR_LED,LOW); // power on the LED
  delayMicroseconds(300);
  float a = analogRead(DIRT_SENSOR_SEN); // read the dust value
  delayMicroseconds(50);
  return a;
}


float getSonarVal(){
  float distance = 0;
  // Set up trigger
  digitalWrite(SONAR1_TRIG,LOW);
  delayMicroseconds(5);
  // Start Measurement
  digitalWrite(SONAR1_TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR1_TRIG,LOW);
  // Acquire and convert to mtrs
  distance=pulseIn(SONAR1_ECHO,HIGH, 60000); // 6000us approximately equal to 100cm 
  sonarRight = distance*0.01657;
  sonarRight = constrain(sonarRight,0,100);
}


float getSonarUart(){
  float temp;
  Serial2.write(0x55);
  if(Serial2.available() >= 2){
    unsigned int MSByteDist = Serial2.read(); // lectura de ambos bytes
    unsigned int LSByteDist  = Serial2.read();
    temp  = (MSByteDist * 256 + LSByteDist)/10.0; // distancia
    temp = constrain(temp,0,100);
    if(temp > 0.0 ){
      sonarMid = temp;
    }
  }
  Serial1.write(0x55);
  if(Serial1.available() >= 2){
    unsigned int MSByteDist = Serial1.read(); // lectura de ambos bytes
    unsigned int LSByteDist  = Serial1.read();
    temp  = (MSByteDist * 256 + LSByteDist)/10.0; // distancia
    temp = constrain(temp,0,100);
    if(temp > 0.0 ){
      sonarLeft = temp;
    }
  }
}

