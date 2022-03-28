#include <L298NX2.h>
#include "Enes100.h"
// #include <FastLED>

#define marker 210
#define pi = 3.14159265359
//Pin assignment////////////////////////
//Left Motors (A)
#define motorPin1 0
#define motorPin2 1 
#define motorPinEnA 3 
//Right Motors (B)
#define motorPin3 6 // Pin  7 of L293
#define motorPin4 5 // Pin  2 of L293
#define motorPinEnB 10
#define LEDpin 12
#define waterLevelPin 12
#define rx 8 //esp2866 module
#define tx 9 //esp2866 module
#define relayPin A1
#define SalinityPin 2
#define photoresistorPin A0
#define echoPin 5 // attach pin D5 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D4 Arduino to pin Trig of HC-SR04
//Threshholds//////////////////
#define turnThreshold 0.2
#define missionDistanceThreshold 0.1
#define Btrim 0
#define Atrim 0
//constants////////////////////////////
const int grid[5][3];
const double Ultrasonicthreshold 50 //threshold for ultrasonic sensor. This is the minumum distance we want the OTV from any obstacle
const int SalinityThreshold = 250; //update
const int photoresistorThreshhold = 50; //update
const int relayTimeOn = 10000; //milliseconds
const int waterLevel60 = 60;
const int waterLevel40 = 40;
const int waterLevel20 = 20;

//global Variables////////////////////
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement



double x, y, theta;
L298NX2 motors(motorPinEnA, motorPin1, motorPin2, motorPinEnB, motorPin3, motorPin4);

//This will run only one time.
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(relayPin, OUTPUT);
  pinMode(waterLevelPin, INPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(SalinityPin, INPUT);
  Enes100.begin("Team 2 Cool", WATER, marker, rx, tx);
  Serial.begin(115200);
  Enes100.println("Begining Mission");
  completeMission();
  postMission();

}

int val = 0;
void loop()
{ 
  celebrate();
}

/*
  Print some informations in Serial Monitor
*/
void printSomeInfo()
{
  Serial.print("Motor A is moving = ");
  Serial.print(motors.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedA());
  Serial.print("Motor B is moving = ");
  Serial.print(motors.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedB());
}

/***
   used to speed up and slowdown motors over time
*/
void move(double time, int velocity, bool forward = true) {
  if (forward) {
    motors.forward();
  } else {
    motors.backward();
  }
  motors.setSpeedA(velocity - Atrim);
  motors.setSpeedB(velocity - Btrim);
  delay(int(time));
}
/***
* stops drive motors
***/
void stopMotion() {
  motors.disable();
}
/***
* turns OTV
***/
void turn(double angle, int velocity, bool left =true) {
  if (left) {
    motors.forwardB();
    motors.backwardA();
  } else {
    motors.backwardB();
    motors.forwardA();
  }
  motors.setSpeedA(velocity - Atrim);
  motors.setSpeedB(velocity - Btrim);
  do {
    update();
  } while (abs(theta - angle) > turnThreshold);
  stopMotion();
}

 /***
    moves OTV to desired coordinate
  ***/
  void moveTo(double newX, double newY) {
    int deviationFromX = x - startX;
double deviationFromTheta = 0;
double newTheta = theta;
updateCoords();
double slope;
do {
  updateCoords();
  slope = (newy-y)/(newX-x)z);
  deviationFromTheta = atan(slope);
  if (deviationFromX < 0) { //need to turn left
    newTheta += deviationFromTheta;
    turn(newTheta, 150);
  } else if (deviationFromX > 0) {//need to turn right
    newTheta -= deviationFromTheta;
    turn(newTheta, 150, false);
  }
} while (abs(newY - y) > missionDistanceThreshold && abs(newX - x) > missionDistanceThreshold);


  }