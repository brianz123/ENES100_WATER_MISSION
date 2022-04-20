/*
    There are two concepts that I am using here to possibly help
*/
#define ENES100_HELPERS
#include "helpers.h"  
#define BOOST_SPEED 255
#define RIGHT_DEADBAND 100
#define LEFT_DEADBAND 100

void setMotors(int left, int right) {
    if (left > 0) {
        digitalWrite(IN1_A, LOW);
        digitalWrite(IN2_A, HIGH);
    } else if (left < 0) {
        digitalWrite(IN1_A, HIGH);
        digitalWrite(IN2_A, LOW);
    }
    analogWrite(EN_A, abs(left)); // Send PWM signal to motor A
    if (right > 0) {
        digitalWrite(IN1_B, LOW);
        digitalWrite(IN2_B, HIGH);
    } else if (right < 0) {
        digitalWrite(IN1_B, HIGH);
        digitalWrite(IN2_B, LOW);
    }
    analogWrite(EN_B, abs(right)); // Send PWM signal to motor B
}


void setMotors(int speed) {
    setMotors(speed, speed);
}
