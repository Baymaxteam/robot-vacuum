void Control_Motion(float Left_Dis, float Mid_Dis, float Right_Dis, float dirty_vol) {
    // 如果三者任意距離在10-40cm,減速, 小於20則優先右轉
    if (Left_Dis <= MidDis_limit ||  Mid_Dis <= MidDis_limit || Right_Dis <= MidDis_limit  ) {
        if (Left_Dis <= SmallDis_limit ||  Mid_Dis <= SmallDis_limit || Right_Dis <= SmallDis_limit  ) {
            ControlBackandRightTurning();
            Serial.println("DIS : touch and turn right");
            Serial3.println("DIS : touch and turn right");
            
        } else{
            motor_automode_SlowForward();
            Serial.println("DIS : slow down");
            Serial3.println("DIS : slow down");
        }
    } else {
        motor_automode_Forward();
        Serial.println("DIS : Forward");
        Serial3.println("DIS : Forward");
        
    }

    if(dirty_vol > dirt_threshold){
      ControlHeavySweep();
      Serial.println("HeavySweep");
      Serial3.println("HeavySweep");
    }
    rb_counter += 1 ;
    Serial3.print("rb_counter: ");
    Serial3.println(rb_counter);
    if(rb_counter > random_backward){
      rb_counter=0;
      random_backward = random(100, 400);
      Serial3.print("New Random: ");
      Serial3.println(random_backward);
      motor_automode_Backward();
      delay(2000);
      motor_automode_RightTurn();
      delay(150);
    }
}

void ControlHeavySweep(){
  // backward and Slow down forward
  motor_automode_Backward();
  delay(400);
  motor_automode_SlowForward();
}

void ControlBackandRightTurning(){
  motor_automode_Backward();
  delay(200);
  motor_automode_RightTurn();
  delay(100);
}

