void Control_Dir(float Left_Dis, float Mid_Dis, float Right_Dis) {

}

void Control_Velocity(float Left_Dis, float Mid_Dis, float Right_Dis) {
    const float MidDis_limit = 40;
    const float SmallDis_limit = 10;
    // 如果三者任意距離在10-40cm,減速, 小於20則優先右轉
    if (Left_Dis <= MidDis_limit ||  Mid_Dis <= MidDis_limit || Right_Dis <= MidDis_limit  ) {
        
        if (Left_Dis <= SmallDis_limit ||  Mid_Dis <= SmallDis_limit || Right_Dis <= SmallDis_limit  ) {
            Serial.println("DIS : touch and turn right");
            ControlBackandRightTurning();
        } else{
            Serial.println("DIS : slow down");
        }
    } else {
        Serial.println("DIS : Forward");
    }
}

void ControlHeavySweep(){
  // backward and Slow down forward
  motor_Backward();
  delay(3000);
  motor_control();
}

void ControlBackandRightTurning(){
  motor_Backward();
  delay(500);
  motor_RightTurn();
  delay(2000); //tuning to 90 degree
}

