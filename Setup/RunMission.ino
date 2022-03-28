

/***
  completes water collection
***/
void completeMission(){
  updateCoords();
  double missionY = 1.45;
  double startX = .55;
  double directionTheta = pi / 2; //direction to point
  if (y > 1) {
    directionTheta = -1 * pi / 2;
    missionY = .55;
  }
  turn(directionTheta, 150);

updateCoords();
int deviationFromX = x - startX;
double deviationFromTheta = 0;
double newTheta = directionTheta;
do {
  updateCoords();
  double yDist = abs(missionY - y);
  deviationFromTheta = atan(yDist / abs(deviationFromX));
  if (deviationFromX < 0) { //need to turn left
    newTheta += deviationFromTheta;
    turn(newTheta, 150);
  } else if (deviationFromX > 0) {
    newTheta -= deviationFromTheta;
    turn(newTheta, 150, false);
  }
} while (abs(y - missionY) > missionDistanceThreshold);
runMission();//completes sampling proccess
move(2, 150, false);
turn(0, 150);
}
/***
  updateCoords coordinates
***/
void updateCoords() {
  if (Enes100.updateLocation()) {
    x = Enes100.location.x; // x Coordinate
    y = Enes100.location.y; // y Coordinate
    theta = Enes100.location.theta; // Theta
  }else{
    updateCoords();
  }
}

void runMission(){
    int waterLevel;
    String watertype[] =  {"FRESH_UNPOLLUTED","FRESH_POLLUTED", "SALT_UNPOLLUTED", "SALT_POLLUTED"};
    char typeOfWater[];
    //TODO read water level
    analogWrite(relayPin, 255);
    delay(relayTimeOn);
    analogWrite(relayPin, 0);
    //TODO determine Pollution

    Enes100.mission(1, waterLevel);
    Enes100.mission(1, typeOfWater);
}
