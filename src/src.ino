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


// control variable
float Kp = 0.5, Ki = 0, Kd = 0.00; //try
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int count_L = 0, count_M = 0, count_R = 0;

int initial_motor_speed = 100; // 降速
int count_cali = 0, flag = 0;
char val = '0';

int on = 0;
unsigned long last = millis();

void calculate_pid(void);
void motor_control(void);
void motor_control_calibration(void);
void motor_control_stop(void);
void motor_test(void);
void InitializeMPU6050() 



void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(ledPower, OUTPUT);
  pinMode(RIGHT_WHEEL_H1, OUTPUT);
  pinMode(RIGHT_WHEEL_H2, OUTPUT);
  pinMode(RIGHT_WHEEL_PWM, OUTPUT);
  pinMode(LEFT_WHEEL_H1,  OUTPUT);
  pinMode(LEFT_WHEEL_H2,  OUTPUT);
  pinMode(LEFT_WHEEL_PWM, OUTPUT);
  delay(5);
}

void loop() {
  digitalWrite(DIRT_SENSOR_LED, LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(DIRT_SENSOR_SEN); // read the dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH); // turn the LED off
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

  if (flag == 0) {
    motor_control_stop();
  } else if (flag == 1) {
    motor_control_calibration();
  } else if (flag == 3) {
    motor_test();
  } else if (flag == -1) {
    motor_Forward();
  }   else if (flag == -2) {
    motor_Backward();
  }   else if (flag == -3) {
    motor_RightTurn();
  }   else if (flag == -4) {
    motor_LeftTurn();
  }
  Serial.print("Flag: ");
  Serial.println(flag);
  delay(200);
}
