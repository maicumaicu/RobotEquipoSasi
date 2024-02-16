void movementMachine(int choice) {
  //showModeNumber(1);
  switch (movement) {
    case OUT:
      runMotor(OFF, &Motors[MOT_IZQ]);
      runMotor(OFF, &Motors[MOT_DER]);
      analogWrite(9, 0);
      analogWrite(11, 0);
      if (choice != OUT) {
        movement = choice;
        counterD = 0;
        counterI = 0;
        offset = getTurnAngle();
      }
      break;
    case ADE:
    //Serial.println("MAP");
      if (calcularDistancia(counterD) < FORWARD_DISTANCE  || calcularDistancia(counterI) < FORWARD_DISTANCE) {
        angularPID(pd[0]);
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        analogWrite(9, 100);
        analogWrite(11, 100);
      } else {
        movimientoFlag = 1;
        movement = OUT;
      }
      break;
    case DER:
    degrees = getTurnAngle();
      Serial.println(degrees);
      if (degrees  >= offset - LEFT_ANGLE_MIN) {
        //Serial.println(getTurnAngle());
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ATRAS, &Motors[MOT_DER]);
        analogWrite(9, TURN_VELOCITY_I);
        analogWrite(11, TURN_VELOCITY_D);
      } else if (degrees  <= offset - LEFT_ANGLE_MAX) {
        runMotor(ATRAS, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        analogWrite(9, TURN_VELOCITY_I);
        analogWrite(11, TURN_VELOCITY_D);
      } else {
        //estabilizationOffset = getTurnAngle();
        movement = ADE;
        
        counterD = 0;
        counterI = 0;
      }
      break;
    case IZQ:
       degrees = getTurnAngle();
      Serial.println(degrees);
      if (degrees  <= LEFT_ANGLE_MIN + offset) {
        //Serial.println(getTurnAngle());
        runMotor(ATRAS, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        analogWrite(9, TURN_VELOCITY_I);
        analogWrite(11, TURN_VELOCITY_D);
      } else if (degrees  >= LEFT_ANGLE_MAX + offset) {
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ATRAS, &Motors[MOT_DER]);
        analogWrite(9, TURN_VELOCITY_I);
        analogWrite(11, TURN_VELOCITY_D);
      } else {
        //estabilizationOffset = getTurnAngle();
        movement = ADE;
        
        counterD = 0;
        counterI = 0;
      }
      break;
    case ATR:
     degrees = getTurnAngle();
      Serial.println(degrees);
      if (degrees  <= LEFT_ANGLE_MIN * 2  + offset) {
        //Serial.println(getTurnAngle());
        runMotor(ATRAS, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        analogWrite(9, TURN_VELOCITY_I);
        analogWrite(11, TURN_VELOCITY_D);
      } else if (degrees  >= LEFT_ANGLE_MAX *2 + offset) {
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ATRAS, &Motors[MOT_DER]);
        analogWrite(9, TURN_VELOCITY_I);
        analogWrite(11, TURN_VELOCITY_D);
      } else {
        //estabilizationOffset = getTurnAngle();
        movement = ADE;
        
        counterD = 0;
        counterI = 0;
      }
      break;
  }
}

void rotateAxis(int direccion) {
  switch (direccion) {
    case DERECHA:
      for (int i = 0; i < 4; i++) {
        direcciones[i] = direcciones[i] - 1;
        if (direcciones[i] == -1) {
          direcciones[i] = 3;
        }
      }
      break;
    case IZQUIERDA:
      for (int j = 0; j < 4; j++) {
        direcciones[j] = direcciones[j] + 1;
        if (direcciones[j] == 4) {
          direcciones[j] = 0;
        }
      }
      break;
  }
}

void resetAxis(int direcciones[4]) {
  for (int i = 0; i < 4; i++) {
    direcciones[i] = i;
  }
}
