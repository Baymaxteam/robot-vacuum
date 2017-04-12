#define SONAR1_TRIG     2
#define SONAR1_ECHO     3
#define SONAR2_TRIG     4
#define SONAR2_ECHO     5
#define RIGHT_WHEEL_H1  6
#define RIGHT_WHEEL_H2  7
#define RIGHT_WHEEL_PWM 8
#define LEFT_WHEEL_H1   9
#define LEFT_WHEEL_H2   10
#define LEFT_WHEEL_PWM  11
#define DIRT_SENSOR_LED 12
#define DIRT_SENSOR_SEN A0

 
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

 
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
}
 
void loop(){
  digitalWrite(DIRT_SENSOR_LED,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  voMeasured = analogRead(DIRT_SENSOR_SEN); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
 
  // 0 - 3.3V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (3.3 / 1024);
 
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 0.17 * calcVoltage - 0.1;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity);
 
  delay(1000);
}
