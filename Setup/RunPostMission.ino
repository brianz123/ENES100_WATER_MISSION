void postMission() {
  if (checkObstacle()) { //if cannot see in 2,1
    moveTo(1, 0);
    if (checkObstacle()) { //if cannot see in 2,0
      moveTo(1, 2);
      moveTo(2, 2);
      if (checkObstacle()) { //if cannot see in 4,2
        moveTo(2, 1)
        if (checkObstacle()) { //if cannot see in 4,1
          moveTo(2, 0);
          moveTo(4, 0);
          moveTo(4, 2);
          moveTo(5, 2);
          celebrate(); //path 1
        } else { //can see in 4,1
          moveTo(4, 1);
          moveTo(4, 2);
          moveTo(5, 2);
          celebrate(); // path 3
        }
      } else { //can see 4,2
        moveTo(5, 2);
        celebrate(); // path 2
      }
    } else { //can see 2,0
      moveTo(2, 0);
      if (checkObstacle()) { //if cannot see in 4,0
        moveTo(2, 1);
        if (checkObstacle()) { //if cannot see in 4,1
          moveTo(2, 2);
          moveTo(5, 2);
          celebrate(); //path 9
        } else {//   can see in 4, 1
          moveTo(4, 1);
          moveTo(4, 2);
          moveTo(5, 2);
          celebrate(); // path 8
        }
      } else { //can see 4,0
        moveTo(4, 0);
        moveTo(5, 2);
        celebrate(); // path 7
      }
    } 
    }else { // can see in 2,1
      moveTo(2, 1);
      if (checkObstacle()) { //if cannot see in 4,1
        moveTo(2, 2);
        if (checkObstacle()) { //if cannot see in 4,2
          moveTo(2, 0);
          moveTo(4, 0);
          moveTo(4, 2);
          moveTo(5, 2);
          celebrate(); //path 5
        } else {//  can see in 4, 2
          moveTo(5, 2);
          celebrate(); //path 6
        }
      } else { //can see in 4,1
        moveTo(4, 1);
        moveTo(4, 2);
        moveTo(5, 2);
        celebrate(); //path 4
      }
    }
}
 
  /***
    returns true if there is no obsticale present
  ***/
  bool checkObstacle() {
    if (getDist() > Ultrasonicthreshold) {
      return true;
    }
    return false;
  }

  /***
    dance party
  ***/
  void celebrate() {
    //TODO
  }
  bool getDist() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  }
  