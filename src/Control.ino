void Control_Motion(float Left_Dis, float Mid_Dis, float Right_Dis, float dirty_vol) {
    // 如果三者任意距離在10-40cm,減速, 小於20則優先右轉
    if (Left_Dis <= MidDis_limit ||  Mid_Dis <= MidDis_limit || Right_Dis <= MidDis_limit  ) {
        if (Left_Dis <= SmallDis_limit ||  Mid_Dis <= SmallDis_limit || Right_Dis <= SmallDis_limit  ) {
            ControlBackandRightTurning();
            Serial.println("DIS : touch and turn right");
            Serial3.println("DIS : touch and turn right");
            
        } else{
            motor_SlowForward();
            Serial.println("DIS : slow down");
            Serial3.println("DIS : slow down");
        }
    } else {
        motor_Forward();
        Serial.println("DIS : Forward");
        Serial3.println("DIS : Forward");
        
    }

    if(dirty_vol > dirt_threshold){
      ControlHeavySweep();
      Serial.println("HeavySweep");
      Serial3.println("HeavySweep");
    }
}

void ControlHeavySweep(){
  // backward and Slow down forward
  motor_Backward();
//  delay(3000);
  motor_control();
}

void ControlBackandRightTurning(){
  motor_Backward();
//  delay(500);
  motor_RightTurn();
//  delay(2000); //tuning to 90 degree
}

