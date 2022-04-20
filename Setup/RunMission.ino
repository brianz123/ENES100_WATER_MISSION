

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
    moveTo(.55, .75);
//    setAngle(directionTheta);
//    moveTo(.55, .75);
//    setAngle(directionTheta);
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

  //updateCoords();
  //double deviationFromX = x - startX;
  //double deviationFromTheta = 0;
  //double newTheta = directionTheta;
  //do {
  //  newTheta = theta;
  //  updateCoords();
  //  double yDist = abs(missionY - y);
  //  deviationFromX = x - startX;
  //  deviationFromTheta = atan(yDist / abs(deviationFromX));
  //  if (deviationFromX > 0) { //need to turn left
  //    newTheta += deviationFromTheta;
  //    turnInPlace(newTheta, 255, true);
  //      Enes100.println("Turn Left");
  //
  //  } else if (deviationFromX > 0) {
  //    newTheta -= deviationFromTheta;
  //    turnInPlace(newTheta, 255, false);
  //    Enes100.println("Turn Right");
  //  }else Enes100.println("straight");
  //  delay(2000);
  //MOVE(250, 255, true);
  ////  stopMotion();
  //  Enes100.print(theta);
  //  Enes100.print(" ");
  //   Enes100.print(newTheta);
  //  Enes100.print(" ");
  //  Enes100.println(x);
  //  Enes100.print(" ");
  //  Enes100.println(startX);
  //
  //
  //  delay(750);
  //} while (abs(y - missionY) > missionDistanceThreshold);
  runMission();//completes sampling proccess
  updateCoords();
  setMotors(-255, -255);
  delay(20);
  setAngle(0); 
}

void runMission() {
  int waterLevel;
  String watertype[] =  {"FRESH_UNPOLLUTED", "FRESH_POLLUTED", "SALT_UNPOLLUTED", "SALT_POLLUTED"};
  String typeOfWater = watertype[1];


  //TODO read water level
////////  EDITTTT
long duration;
int dis;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);

}
void loop() {
  digitalWrite(3, LOW);
  delay(200);
  // trig pin activated for 10 sec
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);


  // reads digital echo and returns sound wave travel time
  duration =  pulseIn(2, HIGH);
  dis = duration*0.0343/2;
  // 20 mm is 10-2, 30 is 9-2, 40 is 8-2 

  //Serial.print("Distance: ");
  //Serial.print(dis);
  //Serial.println(" cm");

  
  if (dis == 7) {
    Serial.println("Water height is 20 mm");
  }
  else if (dis == 6) {
    Serial.println("Water height is 30 mm");
  }
  else if (dis == 5) {
    Serial.println("Water height is 40 mm");
  }
}
///////
  
  analogWrite(relayPin, 255);
  delay(30000);
  analogWrite(relayPin, 0);
  bool isSalty = getSalinity();
    bool isPolluted = false;
  //TODO determine Pollution
  if (isSalty && isPolluted)
    typeOfWater = watertype[3];
  else if (!isSalty && isPolluted)
    typeOfWater = watertype[1];
  else if (!isSalty && !isPolluted)
    typeOfWater = watertype[0];
  else if (isSalty && !isPolluted)
      typeOfWater = watertype[2];

      Serial.println(typeOfWater);

    //     Enes100.mission(1, waterLevel);
    //     Enes100.mission(1, &typeOfWater);
  }
