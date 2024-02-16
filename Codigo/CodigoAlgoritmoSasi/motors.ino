#define FORWARD_DISTANCE 260
#define LEFT_ANGLE_MIN 90
#define LEFT_ANGLE_MAX 96
#define FORWARD_VELOCITY_I 40
#define FORWARD_VELOCITY_D 47
#define TURN_VELOCITY_D 50
#define TURN_VELOCITY_I 50
#define MULTIPLIER 8

float degrees = 0;

void estabilizacion() {
  int diferencia = diferenciaMotores();
  SerialBT.print("dif: " );
  SerialBT.println(diferencia);
  if (diferencia > 0) {
    if (diferencia < 10) {
      powerA = FORWARD_VELOCITY_D + (diferencia * MULTIPLIER);
    } else {
      powerA = FORWARD_VELOCITY_D + (20 * MULTIPLIER);
    }
  } else if (diferencia < 0) {
    if (diferencia > - 10) {
      powerB = FORWARD_VELOCITY_I + (abs(diferencia) * MULTIPLIER);
    } else {
      powerB = FORWARD_VELOCITY_I + (20 * MULTIPLIER);
    }
  } else {
    powerB = FORWARD_VELOCITY_D;
    powerA = FORWARD_VELOCITY_I;
  }
}

int diferenciaMotores() {
  int grados = getTurnAngle() - estabilizationOffset;
  return - grados;
  /*int lecturaD = lecSensor(20, SHARP_D);
    int lecturaI = lecSensor(20, SHARP_I);
    SerialBT.print("D: " );
    SerialBT.println(lecturaD);
    SerialBT.print("I: ");
    SerialBT.println(lecturaI);
    if (lecturaI > 15 && lecturaD > 15) {
    return 0;
    }
    else if (lecturaI > 16 || lecturaI < 3) {
    return lecturaD - (12 - lecturaD);
    }
    else if (lecturaD > 16 || lecturaD < 3) {
    return (12 - lecturaI) - lecturaI;
    } else {
    return lecturaD - lecturaI;
    }*/
}

void movementMachine(int move) {
  switch (movementState) {
    case OFF:
      runOff(powerA, powerB);
      degrees = 0;
      offset = getTurnAngle();
      if (move != OFF) {
        movementState = move;
        SerialBT.println(move);
        counterD = 0;
        counterI = 0;
      }
      break;
    case ADELANTE:
      //SerialBT.print(calcularDistancia(counterI));
      if (calcularDistancia(counterD) < FORWARD_DISTANCE  || calcularDistancia(counterI) < FORWARD_DISTANCE) {
        estabilizacion();
        //powerA = 100;
        //powerB = 100;
        runForward(powerA, powerB);
        //SerialBT.print(calcularDistancia(counterI));
        //SerialBT.print("  ");
        //SerialBT.println(calcularDistancia(counterD));
      } else {
        estabilizationOffset = getTurnAngle();
        movimientoFlag = 1;
        movementState = OFF;
        //SerialBT.print("listo");
      }
      break;
    case IZQUIERDA:

      //SerialBT.println("IZQUIERDA");
      degrees = getTurnAngle();
      //SerialBT.println(degrees);
      if (degrees  <= LEFT_ANGLE_MIN + offset) {
        //SerialBT.println(degrees);
        //SerialBT.println(counterD);
        powerA = TURN_VELOCITY_I;
        powerB = TURN_VELOCITY_D;
        runLeft(powerA, powerB);
      } else if (degrees  >= LEFT_ANGLE_MAX + offset) {
        runRight(powerA, powerB);
      } else {
        //runOff(0, 0);
        estabilizationOffset = getTurnAngle();
        movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
      }
      break;
    case DERECHA:
      //SerialBT.println("DERECHA");
      degrees = abs(getTurnAngle());
      SerialBT.println(degrees);
      if (degrees  <= (LEFT_ANGLE_MIN) + offset) {
        powerA = TURN_VELOCITY_I;
        powerB = TURN_VELOCITY_D;
        runRight(powerA, powerB);
      } else if (degrees  >= LEFT_ANGLE_MAX + offset) {
        runLeft(powerA, powerB);
      } else {
        estabilizationOffset = getTurnAngle();
        movementState = ADELANTE;
        //runOff(0, 0);
        counterD = 0;
        counterI = 0;
      }
      break;
    case ATRAS:
      //SerialBT.println("ATRAS");
      degrees = getTurnAngle();
      //SerialBT.println(degrees);
      if (degrees  <= -(LEFT_ANGLE_MIN) * 2 + offset || degrees  >= -(LEFT_ANGLE_MAX) * 2 + offset) {
        powerA = 50;
        powerB = 50;
        runRight(powerA, powerB);
      } else {
        movementState = ADELANTE;
        counterD = 0;
        counterI = 0;
      }
      break;
    case SUPER:
      int X = directions[m] - '0';
      if (calcularDistancia(counterD) < FORWARD_DISTANCE * X  && calcularDistancia(counterI) < FORWARD_DISTANCE * X) {
        estabilizacion();
        powerA = 200;
        powerB = 200;
        runForward(powerA, powerB);
      } else {
        movimientoFlag = 1;
        movementState = OFF;
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
  pinMode(STBY, OUTPUT);
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
  runMotor(OFF, MOTOR_B);
}

void runLeft(int powerA, int powerB) {
  setPowerMotor(powerA, MOTOR_A);
  setPowerMotor(powerB, MOTOR_B);
  runMotor(OFF, MOTOR_A);
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
