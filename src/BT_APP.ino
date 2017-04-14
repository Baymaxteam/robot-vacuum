void BT_Commend() {
  if (Serial3.available() >= 3) {
    char Header = Serial3.read(); // lectura de ambos bytes
    char Second  = Serial3.read();
    char Cmd  = Serial3.read();
    if (Header == '!' && Second == '@') {
      if (Cmd == 'R' ) {
        Serial.println("BT : turn right");
      } else if (Cmd == 'L') {
        Serial.println("BT : turn left");
      } else if (Cmd == 'F') {
        Serial.println("BT : forward");
      } else if (Cmd == 'B') {
        Serial.println("BT : backward");
      } else if (Cmd == 'A') {
        Serial.println("BT : Auto mode");
      } else if (Cmd == 'C') {
        Serial.println("BT : Manual");
      }
    }
  }
}

