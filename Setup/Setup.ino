#include "Enes100.h"
#define ENES100_HELPERS
#include "helpers.h"
#define marker 214
#define pi 3.14159265359
// Pin assignment////////////////////////
// Left Motors (A)
const unsigned int EN_A = 3;
const unsigned int IN1_A = 8;
const unsigned int IN2_A = 4;
//Right motors
const unsigned int IN1_B = 5;
const unsigned int IN2_B = 6;
const unsigned int EN_B = 10;
const int rx = 12; //esp2866 module
const int tx = 11; //esp2866 module
const int relayPin = A1;
const int TdsSensorPin = A5;
const int photoresistorPin = A2;
const int LED_PIN = 2;
const int echoPin = 7;
const int trigPin = 9;
const int echoPinB = 13;
const int photo2 = A4;
/////////////////////Threshholds//////////////////
#define missionDistanceThreshold 0.15
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point

///////////////constants////////////////////////////
#define ultrasonicThreshold 15          // threshold for ultrasonic sensor. This is the minumum distance we want the OTV from any obstacle
#define SalinityThreshold 500
#define photoresistorThreshhold 50 // update
#define relayTimeOn 55000          // milliseconds

////////////global Variables////////////////////
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;
double x, y, theta;
// This will run only one time.
void setup()
{
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  pinMode(relayPin, OUTPUT);
  //pinMode(waterLevelPin, INPUT);
  pinMode(photoresistorPin, INPUT);
  pinMode(photo2, INPUT);
  pinMode(TdsSensorPin, INPUT);
  Enes100.begin("Team 2 Cool", WATER, marker, rx, tx);
  Serial.begin(115200);
  Enes100.println("Beginning Mission");
  Serial.println("Beginning Mission");
  updateCoords();
   Enes100.println("Starting Mission");
  completeMission();
//  runMission();
  postMission();
  Serial.println(getSalinity());
  Serial.println(" Mission complete");
  Enes100.println(" Mission complete");
}

void loop()
{
//  int s = getSalinity();
//  Serial.println(analogRead(photo2));
  Serial.println(getHeight());
//runMission();
//Enes100.println(analogRead(photo2));
//followline();
delay(1000);
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
   tries to update coordnates until it does successfully
*/
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
/***
   Confirms that OTV is returning reasonable numbers and not garbage values
*/
bool sanityCheck() {
  return Enes100.location.theta < PI * 1.1 &&
         Enes100.location.theta > -PI * 1.1 &&
         Enes100.location.x > -0.1 &&
         Enes100.location.x < 4.1 &&
         Enes100.location.y > -0.1 &&
         Enes100.location.y < 2.1;
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
