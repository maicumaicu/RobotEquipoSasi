float offset = 0;
int giro = 0;
void rotateAxis(int direccion, int direcciones[4]) {
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

void movementMachine(int move) {
  switch (movementState) {
    case OFF:
      /*runMotor(OFF, MOTOR_A);
        runMotor(OFF, MOTOR_B);*/
      if (move != OFF) {
        movementState = move;
        if (move != ADELANTE) {
          counterI = 0;
          counterD = 0;
          offset = 0;

        } else {
          counterI = 100;
          counterD = 100;
          offset = 25.1;
        }
        //intUartSend(TIM3->CNT);
      }
      break;
    case ADELANTE:
      //TIM4->CCR3 = xSpeed;
      //TIM4->CCR4 = xSpeed;
      //intUartSend(TIM1->CNT);
      //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
      objectiveDistance = forwardChoice[choice] + offset;
      //acelerationObjective = offset;
      //if (Sensors[2] > 5) {
      if ((calcularDistancia(counterI)
           + calcularDistancia(counterD)) / 2
          < forwardChoice[choice] + offset
          || (calcularDistancia(counterI)
              + calcularDistancia(counterD) / 2
              > forwardChoice[choice] + offset + 0.5 ) ) {
        //moveStraight();
        StraightFlag = 1;
        KPP = KPPchoice[SLOW];
        KDP = KDPchoice[SLOW];

        //intUartSend(objectiveDistance -(calcularDistancia(TIM3->CNT) + calcularDistancia(TIM1->CNT))/2);
        //intUartSend(1);
        if (direction == ADELANTE) {
          runMotor(ADELANTE, MOTOR_D);
          runMotor(ADELANTE, MOTOR_I);
        } else {
          runMotor(ATRAS, MOTOR_D);
          runMotor(ATRAS, MOTOR_I);
        }

      } else {
        StraightFlag = 0;
        movimientoFlag = 1;
        movementState = OFF;
        runMotor(OFF, MOTOR_D);
        runMotor(OFF, MOTOR_I);
        //      intUartSend(offset);
        aceleration = ADELANTE;
        //TIM3->CNT = 0;
        //TIM1->CNT = 0;

        offset = (calcularDistancia(counterI)
                  + calcularDistancia(counterD)) / 2;
        //HAL_Delay(2000);

        //intUartSend(10);
      }
      /*} else {
        StraightFlag = 0;
        movimientoFlag = 2;
        movementState = OFF;
        offset = (calcularDistancia((TIM3->CNT) >> 1)
        + calcularDistancia((TIM1->CNT) >> 1)) / 2;

        }*/
      break;
    case IZQUIERDA:
      setPowerMotor(IZQUIERDA, baseChoice[choice]
                    - (calcularDistancia(counterI)
                       * (baseChoice[choice] / LeftChoice[choice])
                       - baseChoice[choice] / 1.8));
      setPowerMotor(DERECHA, baseChoice[choice]
                    - (calcularDistancia(counterI)
                       * (baseChoice[choice] / LeftChoice[choice])
                       - baseChoice[choice] / 1.8));
      //intUartSend((TIM3->CNT));
      //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
      if (calcularDistancia(counterD) < LeftChoice[choice]) {
        runMotor(ADELANTE, MOTOR_D);
        runMotor(ATRAS, MOTOR_I);
      } else {
        movementState = ADELANTE;
        runMotor(OFF, MOTOR_D);
        runMotor(OFF, MOTOR_I);
        counterD = 100;
        counterI = 100;
        offset = 25.1;
        //giro = 1;
        //intUartSend(9);
      }
      break;
    case DERECHA:
      //setPowerMotor(IZQUIERDA,xSpeed);
      //setPowerMotor(DERECHA,xSpeed);
      /*TIM4->CCR3 = baseChoice[choice]
              - (calcularDistancia((TIM1->CNT) >> 1)
                    (baseChoice[choice] / LeftChoice[choice])
                  - baseChoice[choice] / 1.3);
          TIM4->CCR4 = baseChoice[choice]
              - (calcularDistancia((TIM1->CNT) >> 1)
                    (baseChoice[choice] / LeftChoice[choice])
                  - baseChoice[choice] / 1.3);*/
      //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
      //intUartSend(TIM1->CNT);
      /*if (calcularDistancia((TIM1->CNT) >> 1) < RightChoice[choice]) {
            runMotor(ATRAS, MOTOR_A);
            runMotor(ADELANTE, MOTOR_B);
        } else {
        //
        movementState = ADELANTE;
        runMotor(OFF, MOTOR_A);
        runMotor(OFF, MOTOR_B);
        TIM3->CNT = 100;
        TIM1->CNT = 100;
        offset = 25.1;
        //intUartSend(8);
        }*/


      objectiveDistance = RightChoice[choice]/* + offset*/;
      if (calcularDistancia(counterD) < RightChoice[choice]
          || calcularDistancia(counterD)
          > RightChoice[choice] + 0.5) {

        StraightFlag = 2;
        KPP = KPPchoice[TURN_90];
        KDP = KDPchoice[TURN_90];
        if (direction == ADELANTE) {

          //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
          runMotor(ATRAS, MOTOR_D);
          runMotor(ADELANTE, MOTOR_I);
        } else {
          //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);

          runMotor(ADELANTE, MOTOR_D);
          runMotor(ATRAS, MOTOR_I);
        }
        //intUartSend("HOLA");
      } else {
        //
        movementState = ADELANTE;
        runMotor(OFF, MOTOR_D);
        runMotor(OFF, MOTOR_I);
        counterI = 100;
        counterD = 100;
        offset = 25.1;
        //intUartSend(8);
      }
      break;
    case ATRAS:
      setPowerMotor(IZQUIERDA, baseChoice[choice]
                   - (calcularDistancia(counterD)
                      * (baseChoice[choice] / LeftChoice[choice])
                      - baseChoice[choice] / 1.3));
      setPowerMotor(DERECHA, baseChoice[choice]
                   - (calcularDistancia(counterD)
                      * (baseChoice[choice] / LeftChoice[choice])
                      - baseChoice[choice] / 1.3));
      objectiveDistance = RightChoice[choice] * 2 + offset;
     // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
      if (calcularDistancia(counterD)
          < RightChoice[choice] * 2 + offset
          || calcularDistancia(counterD)
          > RightChoice[choice] * 2 + 0.5 + offset) {

        StraightFlag = 2;
        KPP = KPPchoice[TURN_90];
        KDP = KDPchoice[TURN_90];
        if (direction == ADELANTE) {
          runMotor(ATRAS, MOTOR_D);
          runMotor(ADELANTE, MOTOR_I);
        } else {
          runMotor(ADELANTE, MOTOR_D);
          runMotor(ATRAS, MOTOR_I);
        }

      } else {

        StraightFlag = 0;
        movementState = ADELANTE;
        runMotor(OFF, MOTOR_D);
        runMotor(OFF, MOTOR_I);
        counterI = 100;
        counterD = 100;
        offset = 25.1;
        //intUartSend(7);
      }
      break;

  }
}
