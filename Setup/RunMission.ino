

/***
  completes water collection
***/
void completeMission() {
  Enes100.println("Mission Start");
  updateCoords();
  double directionTheta = pi / 2; //direction to point
  if (y > 1) {
    directionTheta = -1  *pi / 2 ;
    setAngleMission(directionTheta);
    Enes100.println("more than 1");
    moveToMission(.55, .85);
//    followline();
    double dis = 100;
    double initY = y;
    updateCoords();
//    while (dis > 0.01) { //Within 10 CM
//      updateCoords();
//      dis = abs(initY - .02 - y);
//      setMotors(150);
//      delay(10);
//      setMotors(0);
//    }
  } else {
    Enes100.println("less than 1");
    setAngleMission(directionTheta);
    moveToMission(.55, 1.1);
//    followline();
    double dis = 100;
    double initY = y;
    updateCoords();
//    while (dis > 0.01) { //Within 10 CM
//      updateCoords();
//      dis = abs(initY + .02 - y);
//      setMotors(150);
//      delay(10);
//      setMotors(0);
//    }
  } 
  setMotors(200, 200);
  delay(500);
  setMotors(0);
  setMotors(-150, -150);
  delay(300);
  setMotors(0);
  Enes100.println("At Mission site");
  runMission();//completes sampling proccess
  updateCoords();
  delay(2000);
  setMotors(-255, -255);
  delay(500);
  setAngle(0);
}
/***
 * complete mission tasks
 */
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
  if (isSalty && isPolluted) {
    Enes100.mission(WATER_TYPE, SALT_POLLUTED);
    k = 0;
  }
  else if (!isSalty && isPolluted) {
    Enes100.mission(WATER_TYPE, FRESH_POLLUTED);
    k = 1;
  }
  else if (!isSalty && !isPolluted) {
    Enes100.mission(WATER_TYPE, FRESH_UNPOLLUTED);
    k = 2;
  }
  else if (isSalty && !isPolluted) {
    Enes100.mission(WATER_TYPE, SALT_UNPOLLUTED);
    k = 3;
  }
  Serial.println(WATER_TYPE);
  Enes100.mission(1, waterLevel);
  Enes100.print("Water Height: ");
  Enes100.println(waterLevel);
  Enes100.print("Water Type: ");
  Enes100.println(k);

  Serial.print("Water Height: ");
  Serial.println(waterLevel);
  Serial.print("Water Type: ");
  Serial.println(k);

}
