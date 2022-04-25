
void postMission() {
const double one = 0.73;
const double two = 1.73;
const double three = 2.73;
  moveTo(one, 1);
  Enes100.println("going to 1,1");
  if (checkObstacle()) { //if cannot see in 2,1
    moveTo(.9, .55);
    Enes100.println("going to 1,0.5");
    if (checkObstacle()) { //if cannot see in 2,0
      Enes100.println("going to 1,1.5");
      moveTo(one, 1.5);
      moveTo(two, 1.5);
      if (checkObstacle()) { //if cannot see in 4,2
        Enes100.println("going to 2,1");
        moveTo(two, 1);
        if (checkObstacle()) { //if cannot see in 4,1
          moveTo(two, .5);
          moveTo(2.9, .5);
          moveTo(2.9, 1.5);
          moveTo(3.4, 1.5);
          celebrate(); //path 1
        } else { //can see in 4,1
          moveTo(three, 1);
          moveTo(three, 1.5);
          moveTo(3.3, 1.5);
          celebrate(); // path 3
        }
      } else { //can see 4,2
        moveTo(3.3, 1.5);
        celebrate(); // path 2
      }
    } else { //can see 2,0
      moveTo(two, .5);
      if (checkObstacle()) { //if cannot see in 4,0
        moveTo(two, 1);
        if (checkObstacle()) { //if cannot see in 4,1
          moveTo(two, 1.5);
          moveTo(3.4, 1.5);
          celebrate(); //path 9
        } else {//   can see in 4, 1
          moveTo(2.9, 1);
          moveTo(2.9, 1.5);
          moveTo(3.4, 1.5);
          celebrate(); // path 8
        }
      } else { //can see 4,0
        moveTo(2.9, .5);
        moveTo(2.9, 1.5);
        moveTo(3.4, 1.5);
        celebrate(); // path 7
      }
    }
  } else { // can see in 2,1y7y
    Enes100.println("going to 2,1");
    moveTo(two-.075, 1);
    if (checkObstacle()) { //if cannot see in 4,1
      Enes100.println("going to 2,1.5");
      moveTo(two+.05, 1.5);
      if (checkObstacle()) { //if cannot see in 4,2
        moveTo(two, .5);
        moveTo(2.9, .5);
        moveTo(2.9, 1.5);
        moveTo(3.4, 1.5);
        celebrate(); //path 5
      } else {//  can see in 4, 2
        moveTo(5, 1.5);
        celebrate(); //path 6
      }
    } else { //can see in 4,1
      moveTo(2.9, 1);
      moveTo(2.9, 1.5);
      moveTo(3.4, 1.5);
      celebrate(); //path 4
    }
  }
}

/***
  returns true if there is no obsticale present
***/
bool checkObstacle() {
  setAngle(0);
  if (getDist() < ultrasonicThreshold) {
   Enes100.println("I see Something!");
    setMotors(-255);
    delay(150);
    setMotors(0);
    return true;
  }
     Enes100.println("I see NOTHING!");

  return false;
}

/***
  dance party
***/
void celebrate() {
  setAngle(0);
  setMotors(255);
  delay(750);
  setMotors(255,-255);
}
double getDist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  Serial.println(duration * 0.034 / 2);
  return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}
