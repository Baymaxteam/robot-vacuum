#define SONAR1_TRIG     2
#define SONAR1_ECHO     3
#define SONAR2_TRIG     4
#define SONAR2_ECHO     5
#define SONAR3_TRIG     22
#define SONAR3_ECHO     23
#define RIGHT_WHEEL_H1  6
#define RIGHT_WHEEL_H2  7
#define RIGHT_WHEEL_PWM 8
#define LEFT_WHEEL_H1   9
#define LEFT_WHEEL_H2   10
#define LEFT_WHEEL_PWM  11
#define DIRT_SENSOR_LED 12
#define DIRT_SENSOR_SEN A0

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

float dirtVol, sonar1Val, sonar2Val, sonar3Val;

void calculate_pid(void);
void motor_control(void);
void motor_control_calibration(void);
void motor_control_stop(void);
void motor_test(void);

float getDirtVal(){
  digitalWrite(DIRT_SENSOR_LED,LOW); // power on the LED
  delayMicroseconds(300);
  float a = analogRead(DIRT_SENSOR_SEN); // read the dust value
  delayMicroseconds(50);
  return a;
}

float getSonarVal(int num){
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
 
void setup(){
  Serial.begin(115200);
  Serial3.begin(115200); 
  pinMode(DIRT_SENSOR_LED,OUTPUT);
  pinMode(DIRT_SENSOR_SEN, INPUT);
  pinMode(SONAR1_TRIG,OUTPUT);
  pinMode(SONAR1_ECHO, INPUT);  
  pinMode(SONAR2_TRIG,OUTPUT);
  pinMode(SONAR2_ECHO, INPUT);
  pinMode(SONAR3_TRIG,OUTPUT);
  pinMode(SONAR3_ECHO, INPUT);
  pinMode(RIGHT_WHEEL_H1, OUTPUT);
  pinMode(RIGHT_WHEEL_H2, OUTPUT);
  pinMode(RIGHT_WHEEL_PWM, OUTPUT);
  pinMode(LEFT_WHEEL_H1,  OUTPUT);
  pinMode(LEFT_WHEEL_H2,  OUTPUT);
  pinMode(LEFT_WHEEL_PWM, OUTPUT);
  delay(5);
}
 
void loop(){
  // Dirt sensor
  dirtVol = getDirtVal();
  // Sonar
  sonar1Val = getSonarVal(1);
  sonar2Val = getSonarVal(2);
  sonar3Val = getSonarVal(3);
  
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
