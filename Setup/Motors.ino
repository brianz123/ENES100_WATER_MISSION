/*
    There are two concepts that I am using here to possibly help
*/
#define ENES100_HELPERS
#include "helpers.h"  
#define BOOST_SPEED 255
#define RIGHT_DEADBAND 100
#define LEFT_DEADBAND 100

//left from -256 to 256
void setMotors(int left, int right) {
    //First, we need to calculate the actual motor precentage based on what we are passed.
    //We cannot do this in _setMotors because it uses recursion to help with cold starts.
    //We are adjusting for speeds that the motor will not even move from, even with a cold start help.
//    if (left < 0) left -= LEFT_DEADBAND;
//    if (left > 0) left += LEFT_DEADBAND;
//    if (right < 0) right -= RIGHT_DEADBAND;
//    if (right > 0) right += RIGHT_DEADBAND;
    left = constrain(left, -255, 255);
    right = constrain(right, -255, 255);
    _setMotors(left, right);
}

int d = 0;
int last_left, last_right;

void _setMotors(int left, int right) {
    int setLeft = left, setRight = right;
    bool db = false;

    if (left > 0) {
        digitalWrite(IN1_A, LOW);
        digitalWrite(IN2_A, HIGH);
    } else if (left < 0) {
        digitalWrite(IN1_A, HIGH);
        digitalWrite(IN2_A, LOW);
    }
    last_left = left;
    analogWrite(EN_A, abs(left)); // Send PWM signal to motor A
    if (right > 0) {
        digitalWrite(IN1_B, LOW);
        digitalWrite(IN2_B, HIGH);
    } else if (right < 0) {
        digitalWrite(IN1_B, HIGH);
        digitalWrite(IN2_B, LOW);
    }
    analogWrite(EN_B, abs(right)); // Send PWM signal to motor B
    if (db) {
        delay(10);
        setMotors(setLeft, setRight); //Reset those bad boys to what they should be.
    }
}


void setMotors(int speed) {
    setMotors(speed, speed);
}
