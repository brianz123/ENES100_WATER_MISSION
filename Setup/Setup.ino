#include "Enes100.h"
#include <FastLED.h>
#define ENES100_HELPERS
#include "helpers.h"
#define marker 209
#define pi 3.14159265359
// Pin assignment////////////////////////
// Left Motors (A)
const unsigned int EN_A = 3;
const unsigned int IN1_A = 8;
const unsigned int IN2_A = 4;

const unsigned int IN1_B = 5;
const unsigned int IN2_B = 6;
const unsigned int EN_B = 10;
// #define LEDpin 12
//#define waterLevelPin 12
const int rx = 12; //esp2866 module
const int tx = 11; //esp2866 module
const int relayPin = A1;
const int TdsSensorPin = A5;
const int photoresistorPin = A2;
#define echoPin 7 // attach pin D5 Arduino to pin Echo of HC-SR04
#define trigPin 9  // attach pin D4 Arduino to pin Trig of HC-SR04

// Threshholds//////////////////
#define turnThreshold 0.2
#define missionDistanceThreshold 0.05
#define Btrim 0
#define Atrim 0
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;
// constants////////////////////////////
const int grid[5][3];
#define ultrasonicThreshold 10          // threshold for ultrasonic sensor. This is the minumum distance we want the OTV from any obstacle
const int SalinityThreshold = 250;      // update
const int photoresistorThreshhold = 50; // update
const int relayTimeOn = 2000;          // milliseconds
const int waterLevel60 = 60;
const int waterLevel40 = 40;
const int waterLevel20 = 20;

// global Variables////////////////////
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    70
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
double x, y, theta;
// This will run only one time.
void setup()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
    FastLED.show();
    delay(10);
  }
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  pinMode(relayPin, OUTPUT);
  // pinMode(waterLevelPin, INPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(TdsSensorPin, INPUT);
  Enes100.begin("Team 2 Cool", WATER, marker, rx, tx);
  Serial.begin(115200);
  Enes100.println("Begining Mission");
  Serial.println("Begining Mission");
  //  updateCoords();
  //  setMotors(200, 200);
  //  delay(500);
  //  // completeMission();
  //  //  turnInPlace(pi/2,200,true);
  //  //  updateCoords();
  //  psl("Starting... 1 second delay");
  //  delay(500);
  //  psl("Starting sequence");
  //  //     setAngle(PI/3);
  //  Enes100.println("Angle Found");
  //
  //  moveTo(.55, 1.5);
  //  psl("Done");
  //  moveTo(.4, .4);
  //  moveTo(.75, 1.5);
  //  moveTo(4.15, 1.5);
  //  Enes100.println("Move 2");

  //  printStuff();

//  completeMission();
  runMission();
  //    postMission();
  Serial.println(getSalinity());
  Serial.println(" Mission complete");
  Enes100.println(" Mission complete");
}

int val = 0;
void loop()
{
  //  Serial.println(checkObstacle());
  //   if (!checkObstacle()) {
  //     motorsOff(0);
  //    } else {
  //     MOVE(100, 200, true);
  //    }
  // celebrate();
//    move(1000, 255, true);
  // Serial.println("move");
  //  turn(120, 255, true);
//  Serial.println("turn");
}


/***
  used to speed up and slowdown motors over time
*/
void MOVE(double time, int velocity, bool forward) {
  setSpeed(0, 0);
  setDirection(forward, 0);
  setSpeed(0, velocity);


  delay(int(time));
  motorsOff(0);
}
/***
  turns OTV
***/
void turnInPlace(double angle, int velocity, bool left) {
  setSpeed(1, velocity);
  setSpeed(2, velocity);
  if (left) {
    setDirection(true, 2);
    setDirection(false, 1);
  } else {
    setDirection(true, 1);
    setDirection(false, 2);
  }
  //motors.backward();

  do {
    setSpeed(1, velocity);
    setSpeed(2, velocity);
    if (left) {
      setDirection(true, 2);
      setDirection(false, 1);
    } else {
      setDirection(true, 1);
      setDirection(false, 2);
    }
    updateCoords();
    Enes100.print("Theta: ");
    Enes100.println((theta));
    Enes100.print("Angle: ");
    Enes100.println((angle));
    delay(5);
  }
  while (abs(theta - angle) > pi / 32); //   stopMotion();
  // delay(angle);
  motorsOff(0);
}

void turnAndMove(double angle, int velocity, bool left, int radius) {
  setDirection(true, 0);
  if (left) {
    setSpeed(1, velocity / radius);
    setSpeed(2, velocity);
  } else {
    setSpeed(1, velocity);
    setSpeed(2, velocity / radius);
  }

  do {
    updateCoords();
    Enes100.println("turning");
  }
  while (abs(theta - angle) < pi / 12); //   stopMotion();
  // delay(angle);
  motorsOff(0);
}


/***
   moves OTV to desired coordinate
  ***//*
  void moveTo(double newX, double newY)
  {
  double deviationFromTheta = 0;
  updateCoords();
  double newTheta = theta;
  updateCoords();
  double slope;


  while (abs(newY - y) > missionDistanceThreshold &&
         abs(newX - x) > missionDistanceThreshold){
    updateCoords();
    if (newX - x == 0) {
      if (newY > y)
        newTheta = pi / 2;
      else
        newTheta = 3 * pi / 2;
    } else {
      slope = (newY - y) / (newX - x);
      newTheta = atan(slope);
      Enes100.println("*******");
      Enes100.println(deviationFromTheta);
      Enes100.print("X: ");
      Enes100.print(x);
      Enes100.print(" Y: ");
      Enes100.println(y);
      Enes100.print("Theta: ");
      Enes100.println((theta));
    }
    Enes100.println("#########");
    if (newTheta - theta > 0) { // need to turn left
      turnInPlace(newTheta, 225, true);
    } else if (newTheta - theta < 0) { // need to turn right
      turnInPlace(newTheta, 225, false);
    }

    MOVE(100, 200, true);
    delay(10);
  }

  }

  /***
  update coordinates
***/
void updateCoords()
{
  if (Enes100.updateLocation())
  {
    x = Enes100.location.x;         // x Coordinate
    y = Enes100.location.y;         // y Coordinate
    theta = Enes100.location.theta; // Theta
    //    Enes100.println("Updated Coords");
    if (!sanityCheck()) {
      Enes100.print("Update Coords failed ");
      updateCoords();
    }
  }
  else
  {
    Enes100.print("Update Coords failed ");
    updateCoords();
  }
}
void setDirection(bool forward, int motors) {
  switch (motors) {
    case 0:
      {
        if (forward) {
          //left

          digitalWrite(IN1_A, LOW);
          digitalWrite(IN2_A, HIGH);
          //right
          digitalWrite(IN1_B, LOW);
          digitalWrite(IN2_B, HIGH);
        } else {
          //left
          digitalWrite(IN1_A, HIGH);
          digitalWrite(IN2_A, LOW);
          //right
          digitalWrite(IN1_B, HIGH);
          digitalWrite(IN2_B, LOW);
        }
        break;
      }
    case 1:
      {
        if (forward) {
          //left

          digitalWrite(IN1_A, HIGH);
          digitalWrite(IN2_A, LOW);
          //right
          digitalWrite(IN1_B, LOW);
          digitalWrite(IN2_B, HIGH);
        } else {
          //left
          digitalWrite(IN1_A, LOW);
          digitalWrite(IN2_A, HIGH);
          //right
          digitalWrite(IN1_B, HIGH);
          digitalWrite(IN2_B, LOW);
        }
        break;
      case 2:
        {
          if (forward) {
            //left

            digitalWrite(IN1_A, LOW);
            digitalWrite(IN2_A, HIGH);
            //right
            digitalWrite(IN1_B, HIGH);
            digitalWrite(IN2_B, LOW);
          } else {
            //left
            digitalWrite(IN1_A, HIGH);
            digitalWrite(IN2_A, LOW);
            //right
            digitalWrite(IN1_B, LOW);
            digitalWrite(IN2_B, HIGH);
          }
          break;
        }
      }
  }
}

void setSpeed(int motor, int spd) {
  switch (motor) {
    case 0:
      {
        //        for (int i = 0; i <= spd;i++) {
        int i = spd;
        analogWrite(EN_A, i - Atrim);
        analogWrite(EN_B, i - Btrim);
        delay(1);
        //        }

        break;
      }
    case 1:
      //Left Motor
      analogWrite(EN_A, spd - Atrim);
      break;
    case 2:
      //right motor
      analogWrite(EN_B, spd - Btrim);
      break;
  }
}

void motorsOff(int motor) {
  switch (motor) {
    case 0:
      {
        analogWrite(EN_A, 0);
        analogWrite(EN_B, 0);
        break;
      }
    case 1:
      //Left Motor
      analogWrite(EN_A, 0);
      break;
    case 2:
      //right motor
      analogWrite(EN_B, 0);
      break;
  }
}

void printStuff() {
  updateCoords();

  Enes100.print("X: ");
  Enes100.println((x));
  Enes100.print("Y: ");
  Enes100.println((y));
  Enes100.print("Theta: ");
  Enes100.println((theta));
}
