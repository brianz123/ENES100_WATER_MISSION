#include <Enes100.h>

//To compile you better have helpers.h and Enes100.h. I also edited helpers.h so you need to update it.

const float kP = 100.0;
#define MAX_TURN_SPEED 255


void setAngle(double target) {
  ps("Targeting angle: ");
  pl(target);
  Enes100.updateLocation();
  const double thresh = .15;
  double *curr = &Enes100.location.theta;
  int left = 0, right = 0;

  updateCoords();
  while (abs(target - theta) > thresh) {
    updateCoords();
    if (target - theta > 0) { // need to turn left
      left = MAX_TURN_SPEED;
      right = -1 * MAX_TURN_SPEED;
    } else if (target - theta < 0) { // need to turn right
      left = -1 * MAX_TURN_SPEED;
      right = MAX_TURN_SPEED;
    }
    //    Enes100.print("Theta: ");
    //    Enes100.print(theta);
    //    Enes100.print(" Target: ");
    //    Enes100.println(target);
    setMotors(left, right);
    waitTurn();
  }
  setMotors(0);
}

bool moveTo(double tx, double ty) {
  ps("Going to x:");
  p(tx);
  ps(" y:");
  pl(ty);
  double dis = 100;
  double speed = 0;
  while (dis > missionDistanceThreshold) { //Within 5 CM
    updateCoords();
    dis = sqrt((tx - x) * (tx - x) + (ty - y) * (ty - y));
    //We could go directly to a point, but we could also shoot for a point on a line.
    float angle = atan2(ty - y, tx - x);
    float newTheta = theta + HALF_PI;
    if (newTheta > PI) newTheta -= 2 * PI;
    //Our current will stay the same. It is within the range -pi/2 to 3pi/2
    //Our target anle, however will change based on how we want to approach the thing.
    //For example, if (assume for a second our current is -pi to pi) we are targeting
    //.9pi and are currently at -.9 pi, we should instead try to target -1.1 pi, which is equivalent
    //We will try to find a potential new target.
    //Basically, we should be able to get the target within a pi of the current.
    float delta = abs(angle - theta);
    if (delta > PI) {
      if (angle > PI) {
        angle = angle - 2 * PI;
      }
      else {
        angle = angle + 2 * PI;
      }
    }
    while (angle > PI) {
      angle -= PI;
    }
    while (angle < -1 * PI) {
      angle += PI;
    }
    setAngle(angle);
    speed = 255;
    setMotors(speed);
    if (!waitMove()){
     setMotors(-255);
     delay(750);
     setMotors(0);
      return false; 
    }
    setMotors(0);
  }
return true;
}

void setAngleMission(double target) {
  ps("Targeting angle: ");
  pl(target);
  updateCoords();
  Enes100.updateLocation();
  const double thresh = .04;
  double *curr = &Enes100.location.theta;
  int left = 0, right = 0;
  int speed = 225;
  updateCoords();
  if (target - theta > 0) { // need to turn left
    left = speed;
    right = -1 * speed;
  } else if (target - theta < 0) { // need to turn right
    left = -1 * speed;
    right = speed;
  }
  while (abs(target - theta) > thresh) {

    updateCoords();
    Enes100.print("Theta: ");
    Enes100.print(theta);
    Enes100.print(" Target: ");
    Enes100.println(target);
    setMotors(left, right);
    delay(60);
    setMotors(0);
  }
  setMotors(0);
}

void moveToMission(double tx, double ty) {
  ps("Going to x:");
  p(tx);
  ps(" y:");
  pl(ty);
  double dis = 100;
  double speed = 0;
  setMotors(150);
  delay(250);
  setMotors(0);
  updateCoords();
  //  setAngleMission(atan2(ty - y, tx - x));
  //  setAngleMission(atan2(ty - y, tx - x));
  //  setAngleMission(atan2(ty - y, tx - x));
  while (dis > 0.05) { //Within 10 CM
    updateCoords();
    dis = abs(ty - y);
    //    dis = sqrt((tx - x) * (tx - x) + (ty - y) * (ty - y));
    //We could go directly to a point, but we could also shoot for a point on a line.
    float angle = atan2(ty - y, tx - x);
    float newTheta = theta + HALF_PI;
    if (newTheta > PI) newTheta -= 2 * PI;
    //    ps("c:");
    //    p(toDeg(newTheta));
    //Our current will stay the same. It is within the range -pi/2 to 3pi/2
    //Our target anle, however will change based on how we want to approach the thing.
    //For example, if (assume for a second our current is -pi to pi) we are targeting
    //.9pi and are currently at -.9 pi, we should instead try to target -1.1 pi, which is equivalent
    //We will try to find a potential new target.
    //Basically, we should be able to get the target within a pi of the current.
    float delta = abs(angle - theta);
    if (delta > PI) {
      if (angle > PI) {
        angle = angle - 2 * PI;
      }
      else {
        angle = angle + 2 * PI;
      }
    }
    while (angle > PI) {
      angle -= PI;
    }
    while (angle < -1 * PI) {
      angle += PI;
    }
    //    setAngleMission(atan2(ty - y, tx - x));
    speed = 200;
    //    ps(" s: ");
    //    p(speed);
    setMotors(speed);
    waitMove();
    setMotors(0);
  }

}

/***
   waits until the otv actually moves
*/
bool waitMove() {
  double dis, initX = x, initY = y;
  double init = millis();
  do {
    updateCoords();
    dis = sqrt(pow((initX - x), 2) + pow((initY - y), 2));
    delay(10);
    if (millis() - init > 6000)
      return false;
  } while (dis < .03);
  return true;
}
/***
   waits until the otv actually moves
*/
void waitTurn() {
  double dis, initTheta;
  do {
    updateCoords();
    dis = abs(initTheta - theta);
    delay(10);
  } while (dis < .1);
}

//For TDS sensor
int getMedianNum(int bArray[], int iFilterLen)
{
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}

/***
  return true if salty
*/
bool getSalinity() {
  static unsigned long analogSampleTimepoint = millis();
  analogSampleTimepoint = millis();
  analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
  analogBufferIndex++;
  if (analogBufferIndex == SCOUNT)
    analogBufferIndex = 0;
  //   if(millis()-printTimepoint > 40U)
  //   {
  for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
    analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
  averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) *
                   (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
  float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
  float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
  tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
  //   }
  Serial.println(tdsValue);
  if (tdsValue < SalinityThreshold)
    return false;
  else
    return true;
}

/***
   return the depth of the water in the pool
*/
int getWaterHeight() {
  //TODO read water level
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // trig pin activated for 10 u sec
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // reads digital echo and returns sound wave travel time
  duration =  pulseIn(echoPinB, HIGH);
  distance = duration * 0.0343 / 2;
  // 20 mm is 10-2, 30 is 9-2, 40 is 8-2
  Serial.print("dist: ");
  Serial.println(distance);
  if (distance < 5.5) {
    //      Serial.println("Water height is 20 mm");
    return 40;
  }
  else if (distance < 6.5) {
    //      Serial.println("Water height is 30 mm");
    return 30;
  }
  else if (distance >= 6.5) {
    //      Serial.println("Water height is 40 mm");
    return 20;
  }
}
/***
   returns true if the water has pollution (is green)
*/
bool hasPollution() {
  // read the value from the sensor
  int sensorValue = 0;
  for (int i = 0; i < 100; i++) {
    sensorValue += analogRead(photoresistorPin);
  }
  sensorValue = sensorValue / 100;
  sensorValue = analogRead(photoresistorPin);
  // print the sensor reading so you know its range
  Serial.print("Color ");
  Serial.println(sensorValue);
  // check the pollution
  if (sensorValue < 290) {
    return true;
  }
  return false;
}


/***
   follows the blue line between the mission and landing zone
  // */
//void followline() {
//  while(getHeight() > 8) { //Within 10 CM
//    Enes100.println(analogRead(photo2));
//    //    updateCoords();
////    dis = abs(ty- y);
//    while (analogRead(photo2) >= 285) {
//        Enes100.println(analogRead(photo2));
//      setMotors(200, -250);
//      delay(50);
//      setMotors(0);
//    }
//    while (analogRead(photo2) < 285) {
//        Enes100.println(analogRead(photo2));
//      setMotors(-250, 200);
//      delay(50);
//      setMotors(0);
//    }
//  }
//  setMotors(200, -250);
//  delay(500);
//  setMotors(0);
//}
