void test_commend(int *flag)
{
  char inChar;
  if (Serial.available() > 0) {
    // get incoming byte:
    inChar = Serial.read();

    if (inChar == 'R') {
      *flag = -3;
    } else if (inChar == 'L') {
      *flag = -4;
    } else if (inChar == 'F') {
      *flag = -1;
    } else if (inChar == 'B') {
      *flag = -2;
    } else if (inChar == 'S') {
      *flag = 0;
    }

    Serial.print("received cmd :");
    Serial.write(inChar);
    Serial.println("");
  }
}

void calculate_pid()
{
  P = error;
  I = I + error;;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control() {
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed + PID_value;
  int right_motor_speed = initial_motor_speed - PID_value;

  // The motor speed should not exceed the max PWM value
  constrain(left_motor_speed, 0, 255);
  constrain(right_motor_speed, 0, 255);

  Serial.print("Motor: ");
  Serial.print(left_motor_speed);
  Serial.print(", ");
  Serial.println(right_motor_speed);

  analogWrite(LEFT_WHEEL_PWM, left_motor_speed);  //Left Motor Speed
  analogWrite(RIGHT_WHEEL_PWM, right_motor_speed); //Right Motor Speed
  //following lines of code are to make the bot move forward
  /*The pin numbers and high, low values might be different
  depending on your connections */
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, LOW);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);

}
void motor_control_calibration(){
  //旋轉
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
}

void motor_control_stop(){
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, HIGH);
}

void motor_test(){
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, LOW); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, HIGH);
  delay(control_delay);

  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, LOW);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
  delay(control_delay);
}

void motor_Backward(){
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, LOW);
  digitalWrite(RIGHT_WHEEL_H1, LOW); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, HIGH);
  Serial.println("Motor : Backward");
  delay(2 * control_delay);
}

void motor_Forward(){
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
  Serial.println("Motor : Forward");
  delay(2 * control_delay);

}

void motor_SlowForward(){
  analogWrite(RIGHT_WHEEL_PWM, 50);
  analogWrite(LEFT_WHEEL_PWM, 50);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
  Serial.println("Motor : Slow Forward");
  delay(2 * control_delay);
}

void motor_LeftTurn(){
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, LOW);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
  Serial.println("Motor : Left");
  delay(control_delay);

}

void motor_RightTurn(){
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, LOW); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, HIGH);
  Serial.println("Motor : Right");
  delay(control_delay);
}

