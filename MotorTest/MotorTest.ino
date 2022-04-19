#include "Enes100.h"
#include <IRremote.h>

// #include <FastLED>
int RECV_PIN = 4;          //  The digital pin that the signal pin of the sensor is connected to
IRrecv receiver(RECV_PIN); 
decode_results results;     //  A varuable that would be used by receiver to put the key code into

#define marker 12
#define pi 3.14159265359
// Pin assignment////////////////////////
// Left Motors (A)
const unsigned int EN_A = 3;
const unsigned int IN1_A = 8;
const unsigned int IN2_A = 9;

const unsigned int IN1_B = 5;
const unsigned int IN2_B = 6;
const unsigned int EN_B = 10;
// #define LEDpin 12
//#define waterLevelPin 12
const int rx = 12; //esp2866 module
const int tx = 11; //esp2866 module
#define relayPin A1
#define SalinityPin 2
const int photoresistorPin = A0;
#define echoPin 13 // attach pin D5 Arduino to pin Echo of HC-SR04
//#define trigPin 4  // attach pin D4 Arduino to pin Trig of HC-SR04
#define potPin A5
// Threshholds//////////////////
#define turnThreshold 0.2
#define missionDistanceThreshold 0.2
int Btrim = 0;
int Atrim = 0;
// constants////////////////////////////
const int grid[5][3];
#define ultrasonicThreshold 50          // threshold for ultrasonic sensor. This is the minumum distance we want the OTV from any obstacle
const int SalinityThreshold = 250;      // update
const int photoresistorThreshhold = 50; // update
const int relayTimeOn = 10000;          // milliseconds
const int waterLevel60 = 60;
const int waterLevel40 = 40;
const int waterLevel20 = 20;

// global Variables////////////////////
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

double x, y, theta;

// This will run only one time.
void setup()
{
    receiver.enableIRIn();    //  Enable receiver so that it would start processing infrared signals
  pinMode(EN_A, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  pinMode(relayPin, OUTPUT);
  pinMode(potPin, INPUT);
  // pinMode(waterLevelPin, INPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(SalinityPin, INPUT);
  Enes100.begin("Team 2 Cool", WATER, marker, rx, tx);
  Serial.begin(115200);
  Enes100.println("Begining Mission");
  Serial.println("Begining Mission");
  //completeMission();
  Enes100.println(" Mission complete");

  //  postMission();
}    int code = 1;
bool hardTurn = true;
int spd = 255;
void loop() {
  if (receiver.decode(&results)) {
switch (results.value)
{
case 0xFFA25D: // add trim to A
    Serial.println("Pressed 1");
    Atrim++;
    break;
case 0xFF629D: // clear trim from A
    Serial.println("Pressed 2");
    Atrim = 0;
    break;
case 0xFFE21D: // subtract trim from A
    Serial.println("Pressed 3");
    Atrim--;
    break;
case 0xFF22DD: // Add trim to B
    Serial.println("Pressed 4");
    Btrim++;
    break;
case 0xFF02FD: // clear trim from B
    Serial.println("Pressed 5");
    Btrim = 0;
    break;
case 0xFFC23D: // remove trim from B
    Serial.println("Pressed 6");
    Btrim--;
    break;
case 0xFFE01F:
    Serial.println("Pressed 7");
    break;
case 0xFFA857:
    Serial.println("Pressed 8");
    break;
case 0xFF906F:
    Serial.println("Pressed 9");
    break;
case 0xFF9867:
    Serial.println("Pressed 0");
    break;
case 0xFF6897: // HardTurn On
    Serial.println("Pressed *");
    hardTurn = true;
    break;
case 0xFFB04F: // hardTurn off
    Serial.println("Pressed #");
    hardTurn = false;
    break;
case 0xFF18E7: // forward
    Serial.println("Pressed UP");
    code = 1;
    break;
case 0xFF5AA5:
    Serial.println("Pressed RIGHT");
    code = 2;
    break;
case 0xFF38C7:
    Serial.println("Pressed OK");
    code = 3;
    break;
case 0xFF4AB5:
    Serial.println("Pressed DOWN");
    code = 4;
    break;
case 0xFF10EF:
    Serial.println("Pressed LEFT");
    code = 5;
    break;
}
   //  Decode the button code and put it in "results" variable
    receiver.resume();                        //  Continue listening for new signals
  }
switch (code)
{

case 1: // forward
    Serial.println("Pressed UP");
    MOVE(100, 255, true);
    break;
case 2:
    Serial.println("Pressed RIGHT");
    if (hardTurn)
    {
        turnInPlace(100, 255, false);
    }
    else
    {
        turnAndMove(100, 255, false, 2);
    }
    break;
case 3:
    Serial.println("Pressed OK");
    motorsOff(0);
    break;
case 4:
    Serial.println("Pressed DOWN");
    MOVE(100, 255, false);

    break;
case 5:
    Serial.println("Pressed LEFT");
    if (hardTurn)
    {
        turnInPlace(100, 255, true);
    }
    else
    {
        turnAndMove(100, 255, true, 2);
    }
    break;
}

   

}
/*
  Print some informations in Serial Monitor
*/


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

  //do{
  //  updateCoords();
  //  Enes100.println("turning");
  //  }
  //  while(abs(theta-angle) < pi/12);  //   stopMotion();
  delay(angle);
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

  //do{
  //  updateCoords();
  //  Enes100.println("turning");
  //  }
  //  while(abs(theta-angle) < pi/12);  //   stopMotion();
  delay(angle);
  motorsOff(0);
}


void updateCoords()
{
  if (Enes100.updateLocation())
  {
    x = Enes100.location.x;         // x Coordinate
    y = Enes100.location.y;         // y Coordinate
    theta = Enes100.location.theta; // Theta
    //    Enes100.println("Updated Coords");
  }
  else
  {
    Enes100.print("Updat Coords failed ");

    updateCoords();
  }
}
