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

// Robot behavior setting
const float MidDis_limit = 25;
const float SmallDis_limit = 15;
const float dirt_threshold = 100;
const int motor_offset=20;
int random_backward=100, rb_counter=0;

const int control_delay = 200;

void calculate_pid(void);
void motor_control(void);
void motor_control_calibration(void);
void motor_control_stop(void);
void motor_test(void);
void motor_automode_RightTurn();
void motor_automode_Forward();
void motor_automode_SlowForward();

void Control_Motion(float Left_Dis, float Mid_Dis, float Right_Dis, float dirty_vol);
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

  // Sonar
  getSonarUart();
  getSonarVal();
  Serial.print("dirtVol: ");
  Serial.print(dirtVol);
  Serial.print(", Sonar: ");
  Serial.print(sonarLeft);Serial.print(", ");
  Serial.print(sonarMid);Serial.print(", ");
  Serial.print(sonarRight);Serial.println("");

  Serial3.print("dirtVol: ");
  Serial3.print(dirtVol);
  Serial3.print(", Sonar: ");
  Serial3.print(sonarLeft);Serial3.print(", ");
  Serial3.print(sonarMid);Serial3.print(", ");
  Serial3.print(sonarRight);Serial3.println("");
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
  BT_Commend();
  Serial3.print("Flag: ");
  Serial3.println(flag);
  Serial3.println("");
  Serial3.print("robot_state: ");
  Serial3.println(robot_state);
  Serial3.println("");
  if(robot_state==0){ // 0: manual mode, >1: auto mode
    // test_commend(&flag);
    if (flag == 0) {
      motor_control_stop();
    } else if (flag == 1) {
      motor_control_calibration();
    } else if (flag == 3) {
      motor_test();
    } else if (flag == -1) {
      motor_Forward();
      flag = 0;
    }   else if (flag == -2) {
      motor_Backward();
       flag = 0;
    }   else if (flag == -3) {
      motor_RightTurn();
       flag = 0;
    }   else if (flag == -4) {
      motor_LeftTurn();
      flag = 0;
    }

  }
  else if(robot_state == 1){
    flag = 100;
    Control_Motion(sonarLeft,sonarMid,sonarRight, dirtVol);
    if (flag == 0){
      robot_state = 0;
      motor_control_stop();
    }
  }
  
//  delay(100);
}
