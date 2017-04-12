void Control_Dir(float Left_Dis, float Mid_Dis, float Right_Dis) {

}

void Control_Velocity(float Left_Dis, float Mid_Dis, float Right_Dis) {
    const float MidDis_limit = 40;
    const float SmallDis_limit = 20;
    // 如果三者任意距離在20-40cm,減速, 小於20則優先右轉
    if (Left_Dis <= MidDis_limit ||  Left_Dis <= MidDis_limit || Left_Dis <= MidDis_limit  ) {
        
        if (Left_Dis <= SmallDis_limit ||  Left_Dis <= MidDis_limit || Left_Dis <= MidDis_limit  ) {
            Serial.println("DIS : touch and turn right");
        } else{
            Serial.println("DIS : slow down");
        }
    } else {
        Serial.println("DIS : Forward");
    }

}
