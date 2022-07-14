
void movementMachine() {
  switch (movementState) {
    case OFF:
      runOff();
      move = ChooseNextNode(actual.x, actual.y) ;
      if (move != OFF) {
        movementState = move;
        counter1 = 0;
        counter2 = 0;
      }
      break;
    case ADELANTE:
      if (calculoDistancia(counterD) < FORWARD_DISTANCE && calculoDistancia(counterI) < FORWARD_DISTANCE) {
        runForward(powerA, powerB);
      } else {
        movementState = OFF;
      }
      break;
    case IZQUIERDA:
      if (calculoDistancia(counterD) < -LEFT_DISTANCE && calculoDistancia(counterI) < LEFT_DISTANCE) {
        runLeft(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counter1 = 0;
        counter2 = 0;
      }
      break;
    case DERECHA:
      if (calculoDistancia(counter1) < RIGHT_DISTANCE && calculoDistancia(counter2) < - RIGHT_DISTANCE) {
        runRight(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counter1 = 0;
        counter2 = 0;
      }
      break;
    case ATRAS:
      if (calculoDistancia(counter1) < RIGHT_DISTANCE * 2  && calculoDistancia(counter2) < - RIGHT_DISTANCE * 2 ) {
        runRight(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counter1 = 0;
        counter2 = 0;
      }
      break;
  }
}

void initializeMotors () {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}


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

void runOff() {
  setPowerMotor(100, MOTOR_A);
  setPowerMotor(100, MOTOR_B);
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
      break;
  }
}
