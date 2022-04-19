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
          int i =spd;
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
