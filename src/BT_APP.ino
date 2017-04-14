void BT_Commend() {
  if (Serial3.available() >= 3) {
    char Header = Serial3.read(); // lectura de ambos bytes
    char Second = Serial3.read();
    char Cmd  = Serial3.read();
    if (Header == 'A' && Second == 'B') {
      if (Cmd == 'R' ) {
        Serial.println("BT : turn right");
        flag = -3;
      } else if (Cmd == 'L') {
        Serial.println("BT : turn left");
        flag = -4;
      } else if (Cmd == 'F') {
        Serial.println("BT : forward");
        flag = -1;
      } else if (Cmd == 'B') {
        Serial.println("BT : backward");
        flag = -2;
      } else if (Cmd == 'S') {
        Serial.println("BT : stop");
        flag = 0;
      } else if (Cmd == 'A') {
        Serial.println("BT : Auto mode");
        robot_state=1;
      } else if (Cmd == 'H') {
        Serial.println("BT : Manual mode");
        robot_state=0;
        flag = 0;
      }
    }
  }
}

