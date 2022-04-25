

/***
  completes water collection
***/
void completeMission() {
  Enes100.println("Mission Start");
  updateCoords();
  double missionY = 1.45;
  double startX = .55;
  double directionTheta = pi / 2; //direction to point
  if (y > 1) {
    directionTheta = -1 * pi / 2;
    setAngle(directionTheta);
    Enes100.println("more than 1");
    setAngleMission(directionTheta);
    moveToMission(.55, .9);
    setAngleMission(directionTheta);
  } else {
    Enes100.println("less than 1");
    setAngleMission(directionTheta);
    //    moveTo(.55, 1);
    setAngleMission(directionTheta);
    moveToMission(.55, 1.1);
    setAngleMission(directionTheta);
    //    moveToMission(.55, 1.15);
    //    setAngle(directionTheta);
  }
  Enes100.println("At Mission sight");
//  runMission();//completes sampling proccess
  updateCoords();
  delay(2000);
  setMotors(-255, -255);
  delay(500);
  setAngle(0);
}

void runMission() {
  int waterLevel  = getWaterHeight();
  Serial.println(waterLevel);
  analogWrite(relayPin, 255);
  delay(relayTimeOn);
  analogWrite(relayPin, 0);
  int k = 0; 
  bool isSalty = getSalinity();
  bool isPolluted = hasPollution(); //TODO add fucntion
  //TODO determine Pollution
  if (isSalty && isPolluted){
    Enes100.mission(WATER_TYPE, SALT_UNPOLLUTED);
    k =0;
  }
  else if (!isSalty && isPolluted){
  Enes100.mission(WATER_TYPE, FRESH_POLLUTED);
  k =1;
  }
  else if (!isSalty && !isPolluted){
  Enes100.mission(WATER_TYPE, FRESH_UNPOLLUTED);
  k =2;
  }
  else if (isSalty && !isPolluted){
  Enes100.mission(WATER_TYPE, SALT_UNPOLLUTED);
  k=3;
  }
//  Serial.println(typeOfWater);

       Enes100.mission(1, waterLevel);
       Serial.print("Water Height: ");
        Serial.println(waterLevel);
        Serial.print("Water Type: ");
        Serial.println(k);
       
}
