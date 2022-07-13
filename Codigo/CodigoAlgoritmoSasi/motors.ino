void runForward() {
  setPowerMotor(100, MOTOR_A);
  setPowerMotor(100, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runBackwards() {
  setPowerMotor(100, MOTOR_A);
  setPowerMotor(100, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runRight() {
  setPowerMotor(100, MOTOR_A);
  setPowerMotor(100, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runLeft() {
  setPowerMotor(100, MOTOR_A);
  setPowerMotor(100, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void setPowerMotor(int power, int motor) {
  if (motor == MOTOR_A) {
    analogWrite(PWMA, power);
  } else {
    analogWrite(PWMB, power);
  }
}

void runMotor (int dir, int motor) {
  switch (dir) {
    case ADELANTE:
      if (motor == MOTOR_A) {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
      } else {
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
      }
      break;
    case ATRAS:
      if (motor == MOTOR_A) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
      } else {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
      }
      break;
  }
}
