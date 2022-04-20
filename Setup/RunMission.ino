

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
    missionY = .55;
    Enes100.println("more than 1");
    setAngle(directionTheta);
    moveTo(.55, .7);
    //    setAngle(directionTheta);
    //    moveTo(.55, .75);
    setAngle(directionTheta);
  } else {
    Enes100.println("less than 1");
    setAngle(directionTheta);
    //    moveTo(.55, 1);
    setAngle(directionTheta);
    moveTo(.55, 1.15);
    setAngle(directionTheta);
    //    moveToMission(.55, 1.15);
    //    setAngle(directionTheta);
  }
  Enes100.println("At Mission sight");
  runMission();//completes sampling proccess
  updateCoords();
  setMotors(-255, -255);
  delay(250);
  setAngle(0);
}

void runMission() {
  int waterLevel  = getWaterHeight();
  analogWrite(relayPin, 255);
  delay(relayTimeOn);
  analogWrite(relayPin, 0);
  bool isSalty = getSalinity();
  bool isPolluted = hasPollution(); //TODO add fucntion
  //TODO determine Pollution
  if (isSalty && isPolluted)
    Enes100.mission(WATER_TYPE, SALT_UNPOLLUTED);
  else if (!isSalty && isPolluted)
  Enes100.mission(WATER_TYPE, FRESH_POLLUTED);
  else if (!isSalty && !isPolluted)
  Enes100.mission(WATER_TYPE, FRESH_UNPOLLUTED);
  else if (isSalty && !isPolluted)
  Enes100.mission(WATER_TYPE, SALT_UNPOLLUTED);
//  Serial.println(typeOfWater);

       Enes100.mission(DEPTH, waterLevel);
       
}
