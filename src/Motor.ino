void calculate_pid()
{
  P = error;
  I = I + error;;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
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
void motor_control_calibration()
{
  //旋轉
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
}

void motor_control_stop()
{
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, HIGH);
}

void motor_test()
{
  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, LOW); //MoterB
  digitalWrite(LEFT_WHEEL_H2, HIGH);
  digitalWrite(RIGHT_WHEEL_H1, LOW); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, HIGH);
  delay(1000);

  analogWrite(RIGHT_WHEEL_PWM, 100);
  analogWrite(LEFT_WHEEL_PWM, 100);
  digitalWrite(LEFT_WHEEL_H1, HIGH); //MoterB
  digitalWrite(LEFT_WHEEL_H2, LOW);
  digitalWrite(RIGHT_WHEEL_H1, HIGH); //MoterA
  digitalWrite(RIGHT_WHEEL_H2, LOW);
  delay(1000);
}

