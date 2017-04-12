#define DIRT_SENSOR_LED 12
#define DIRT_SENSOR_SEN A0

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(DIRT_SENSOR_LED,OUTPUT);
 pinMode(DIRT_SENSOR_SEN,INPUT);
}

void loop() {
  digitalWrite(DIRT_SENSOR_LED,LOW); // power on the LED
  delayMicroseconds(samplingTime);
 
  float voMeasured = analogRead(DIRT_SENSOR_SEN); // read the dust value
 
  delayMicroseconds(deltaTime);
  digitalWrite(DIRT_SENSOR_LED,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  
  // 0 - 5.0V mapped to 0 - 1023 integer values
  // recover voltage
  float calcVoltage = voMeasured * (5.0 / 1024);

  float dustDensity = 0.17 * calcVoltage ;

  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity);
}
