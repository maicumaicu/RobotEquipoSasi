#define FORWARD_DISTANCE 100
#define LEFT_ANGLE 90
#define RIGHT_ANGLE 90

float degrees = 0;

void movementMachine() {
  switch (movementState) {
    case OFF:
      runOff(powerA, powerB);
      degrees = 0;
      offset = offset + getTurnAngle();
      move = IZQUIERDA; //ChooseNextNode(actual.x, actual.y) ;
      SerialBT.println("OFF");
      if (move != OFF) {
        movementState = move;
        timer = millis();

        counterD = 0;
        counterI = 0;
      }
      break;
    case ADELANTE:
      //SerialBT.println("ADELANTE");
      if (calcularDistancia(counterD) < FORWARD_DISTANCE  && calcularDistancia(counterI) < FORWARD_DISTANCE) {
        SerialBT.println(counterD);
        runForward(powerA, powerB);
      } else {
        runOff(powerA, powerB);//movementState = OFF;
      }
      break;
    case IZQUIERDA:
      //SerialBT.println("IZQUIERDA");
      degrees = getTurnAngle();
      if (degrees  <= LEFT_ANGLE + offset) {
        SerialBT.println(degrees);
        //SerialBT.println(counterD);
        runLeft(powerA, powerB);
      } else {
        runOff(0, 0);
        //movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
      }
      break;
    case DERECHA:
      SerialBT.println("DERECHA");
      if (getTurnAngle() <= -(RIGHT_ANGLE) ) {
        runRight(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
      }
      break;
    case ATRAS:
      SerialBT.println("ATRAS");
      if (getTurnAngle() <= RIGHT_ANGLE * 2 ) {
        runRight(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
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


void runForward(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runBackwards(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runRight(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ADELANTE, MOTOR_A);
  runMotor(ATRAS, MOTOR_B);
}

void runLeft(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(ATRAS, MOTOR_A);
  runMotor(ADELANTE, MOTOR_B);
}

void runOff(int powerA, int powerB) {
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
      break;
  }
}
