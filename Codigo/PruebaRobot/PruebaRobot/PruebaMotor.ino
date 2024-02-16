#define POWER_B 50
#define POWER_A 50

void initializeMotors () {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}



void runForward() {
  setPowerMotor(POWER_A, MOTOR_A);
  setPowerMotor(POWER_B, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runBackwards() {
  setPowerMotor(POWER_A, MOTOR_A);
  setPowerMotor(POWER_B, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runRight() {
  setPowerMotor(POWER_A, MOTOR_A);
  setPowerMotor(POWER_B, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runLeft() {
  setPowerMotor(POWER_A, MOTOR_A);
  setPowerMotor(POWER_B, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runOff() {
  setPowerMotor(0, MOTOR_A);
  setPowerMotor(0, MOTOR_B);
  runMotor(OFF, MOTOR_A);
  runMotor(OFF, MOTOR_B);
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
    case OFF:
      if (motor == MOTOR_A) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
      } else {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
      }
  }
}
