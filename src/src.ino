#define SONAR1_TRIG     2
#define SONAR1_ECHO     3
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

int robot_state = 0; // 0: manual mode, >1: auto mode

float dirtVol, sonarLeft, sonarMid, sonarRight;

void calculate_pid(void);
void motor_control(void);
void motor_control_calibration(void);
void motor_control_stop(void);
void motor_test(void);

void Control_Velocity(float Left_Dis, float Mid_Dis, float Right_Dis);
void Control_Dir(float Left_Dis, float Mid_Dis, float Right_Dis);
void ControlHeavySweep();
void ControlBackandRightTurning();

void test_commend(int *flag);

float getSonarVal();
float getDirtVal();
float getSonarUart();

void getSensorsValue(){
  // Dirt sensor
  dirtVol = getDirtVal();
  Serial.print("dirtVol: ");
  Serial.print(dirtVol);
  // Sonar
  getSonarUart();
  getSonarVal();
  Serial.print(", Sonar: ");
  Serial.print(sonarLeft);Serial.print(", ");
  Serial.print(sonarMid);Serial.print(", ");
  Serial.print(sonarRight);Serial.println("");
}

void setup(){
  Serial.begin(115200);
  Serial1.begin(9600); // Sonar No. 2
  Serial2.begin(9600); // Sonar No. 3
  Serial3.begin(115200); 
  pinMode(DIRT_SENSOR_LED,OUTPUT);
  pinMode(DIRT_SENSOR_SEN, INPUT);
  pinMode(SONAR1_TRIG,OUTPUT);
  pinMode(SONAR1_ECHO, INPUT);  
  pinMode(RIGHT_WHEEL_H1, OUTPUT);
  pinMode(RIGHT_WHEEL_H2, OUTPUT);
  pinMode(RIGHT_WHEEL_PWM, OUTPUT);
  pinMode(LEFT_WHEEL_H1,  OUTPUT);
  pinMode(LEFT_WHEEL_H2,  OUTPUT);
  pinMode(LEFT_WHEEL_PWM, OUTPUT);
  delay(5);
}

 
void loop(){

  getSensorsValue();
  
  if(robot_state==0){ // 0: manual mode, >1: auto mode
    test_commend(&flag);
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
    Serial.println("");
  }
  else if(robot_state == 1){
    Control_Velocity(sonarLeft,sonarMid,sonarRight);
  }
  
  delay(100);
}
