void mainMachine() {
  switch (mainState) {
  case SETUP:
    actual.x = ALTO;
    actual.y = ANCHO;
    /*visual.x = 0;
     visual.y = 0;*/
    resetAxis(direcciones);
    movimientoFlag = 0;
    finishFlag = 0;
    /*if (Sensors[1] - Sensors[3] < 0.5 && Sensors[1] - Sensors[3] > -0.5) {
     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
     } else {
     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
     }*/
    if (btns[0].flag == 1) {
      // Set The LED ON!
      choice = SLOW;
      velocity = velocityChoice[SLOW];
      setPowerMotor(IZQUIERDA,baseChoice[SLOW]);
      setPowerMotor(DERECHA,baseChoice[SLOW]);
      KPT = KPTchoice[SLOW];
      KDT = KDTchoice[SLOW];
      KPA = KPAchoice[SLOW];
      KDA = KDAchoice[SLOW];
      KPP = KPPchoice[SLOW];
      KDP = KDPchoice[SLOW];
      if (t == 0) {
        mainState = CALIBRATE;
        t++;
      } else {
        mainState = MAPPING;
      }

    }
    if (btns[1].flag == 1) {
      // Set The LED ON!
      choice = FAST;
      velocity = velocityChoice[FAST];
      setPowerMotor(IZQUIERDA,baseChoice[FAST]);
      setPowerMotor(DERECHA,baseChoice[FAST]);
      KPT = KPTchoice[FAST];
      KDT = KDTchoice[FAST];
      KPA = KPAchoice[FAST];
      KDA = KDAchoice[FAST];
      KPP = KPPchoice[FAST];
      KDP = KDPchoice[FAST];
      mainState = RACING;
     //Flash_Read_Data(0x0801FC00, Rx_Data, 2);
      //Convert_To_Str(Rx_Data, string);
      //directions = ReadRun();
      //ShowRun();
    }
    if (btns[2].flag == 1) {
      // Set The LED ON!
      //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
      choice = FAST;
      velocity = velocityChoice[FAST];
       setPowerMotor(IZQUIERDA,baseChoice[FAST]);
      setPowerMotor(DERECHA,baseChoice[FAST]);
      KPT = KPTchoice[FAST];
      KDT = KDTchoice[FAST];
      KPA = KPAchoice[FAST];
      KDA = KDAchoice[FAST];
      KPP = KPPchoice[FAST];
      KDP = KDPchoice[FAST];
      if (t == 0) {
        mainState = CALIBRATE;
        t++;
      } else {
        mainState = MAPPING;
      }
    }
    //confirmacionCentrado();
    break;
  case CALIBRATE:
    calibrateMachine();
    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    break;
  case MAPPING:
    if (finishFlag == 0) {
      robotMachine();
      /*TX_BUFFER[0] = 'L';
       HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);*/
    } else {
      actual.x = ALTO;
      actual.y = ANCHO;
      //visual.x = 0;
      //visual.y = 0;
      finishFlag = 0;
      resetAxis(direcciones);
      //PrintMap();
      mainState = RESOLUTION;
    }
    break;
  case RESOLUTION:
    if (Map[actual.x][actual.y].final == 0) {
      addDirection(actual.x, actual.y);
    } else {
      //directions = optimizeDirections(directions);
      //SerialBT.println(directions);
      // UploadRun(directions);
      directions[directionsSize] = 'o';
      //Flash_Write_Data(0x0801FC00, (uint32_t*) directions, 25);
      mainState = SETUP;
    }

    break;
  case RACING:
    runDirections(string);
    break;
  }

}

void calibrateMachine() {
  switch (calState) {
  case CENTER:
    if (Sensors[1] - Sensors[3] < 0.5 && Sensors[1] - Sensors[3] > -0.5) {
      if (btns[0].flag == 1) {
        CenterDistanceRight = Sensors[3];
        CenterDistanceLeft = Sensors[1];
        calState = LEFT;
      }
    }
    /*runMotor(ADELANTE, MOTOR_A);
     runMotor(ADELANTE, MOTOR_B);
     StraightFlag = 1;*/
    break;
  case LEFT:
    if (btns[0].flag == 1) {
      maxDistance[1] = Sensors[3] + 2;
      calState = RIGHT;
    }
    break;
  case RIGHT:
    if (btns[0].flag == 1) {
      maxDistance[2] = Sensors[1] + 2;
      calState = FORWARD;
    }
    break;
  case FORWARD:
    if (btns[0].flag == 1) {
      maxDistance[0] = Sensors[2];
      mainState = SETUP;
      calState = CENTER;
    }
    break;
  }
}

void robotMachine() {
  switch (robotState) {
  case READING:
    Map[actual.x][actual.y].visitado++;

    if (Map[actual.x][actual.y].visitado == 1) {
      runMotor(OFF, MOTOR_D);
      runMotor(OFF, MOTOR_I);
      CreateNode(&Map[actual.x][actual.y], Sensors, direcciones,
          maxDistance);
      if (q == 1) {
        Map[actual.x][actual.y].Lados[direcciones[ATRAS]] = 1;
        q = 0;
      }
    }
    /*TX_BUFFER[0] = 'D';
     TX_BUFFER[1] = Map[actual.x][actual.y].Lados[DERECHA] + '0';
     TX_BUFFER[2] = '\n';
     TX_BUFFER[3] = 'C';
     TX_BUFFER[4] = Map[actual.x][actual.y].Lados[ADELANTE] + '0';
     TX_BUFFER[5] = '\n';
     TX_BUFFER[6] = 'I';
     TX_BUFFER[7] = Map[actual.x][actual.y].Lados[IZQUIERDA] + '0';
     TX_BUFFER[8] = '\n';
     TX_BUFFER[9] = 'A';
     TX_BUFFER[10] = Map[actual.x][actual.y].Lados[ATRAS] + '0';
     TX_BUFFER[11] = '\n';
     HAL_UART_Transmit(&huart1, TX_BUFFER, 12, 100);
     */
    valueCNY = NEGRO;     //Sensors[0];
    if (valueCNY == BLANCO) {
      Map[actual.x][actual.y].final = 1;
      finishFlag = 1;
    } else {
      Map[actual.x][actual.y].final = 0;
      robotState = CHOOSING;
    }
    //PrintMap();
    //HAL_Delay(1000);
    break;
  case CHOOSING:
    movimiento = ChooseNextNode(actual.x, actual.y);
    movimientoFlag = 0;
    ticksNow = millis();
    robotState = MOVING;

    break;
  case MOVING:
    //TX_BUFFER[0] = 'M';
    //HAL_UART_Transmit(&huart1, TX_BUFFER, sizeof(TX_BUFFER), 100);

    movementMachine(movimiento);
    if (movimientoFlag == 1) {
      robotState = READING;
      //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    }
    break;
  }
}

void runDirections(char moves[100]) {
  if (moves[m] == 'a') {
    movementMachine(ADELANTE);
  } else if (moves[m] == 'd') {
    movementMachine(DERECHA);
  } else if (moves[m] == 'i') {
    movementMachine(IZQUIERDA);
  } else if (moves[m] == 'o') {
    movementMachine(OFF);
  } else {
    movementMachine(SUPER);
  }
  if (movimientoFlag == 1) {
    m++;
    movimientoFlag = 0;
  }
}

void addDirection(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
    //Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE], &actual);
    directions[directionsSize] = 'a';
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
    //Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA], &actual);
    rotateAxis(IZQUIERDA, direcciones);
    directions[directionsSize] = 'i';
  } else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
    //Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA], &actual);
    rotateAxis(DERECHA, direcciones);
    directions[directionsSize] = 'd';
  }
  directionsSize++;
}

int ChooseNextNode(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
//    TX_BUFFER[0] = 'A';
  //  TX_BUFFER[1] = '\n';
    //HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    /*if (Map[x][y].visitado > 1) {
     EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
     direcciones[ATRAS]);
     intUartSend(5000);
     }*/
    if (Map[x][y].Lados[direcciones[ATRAS]] != 1)
      Map[x][y].Lados[direcciones[ATRAS]] = 2;
    last.x = actual.x;
    last.y = actual.y;
    /*intUartSend(Map[actual.x][actual.y].Lados[DERECHA]);
    intUartSend(Map[actual.x][actual.y].Lados[ADELANTE]);
    intUartSend(Map[actual.x][actual.y].Lados[IZQUIERDA]);
    intUartSend(Map[actual.x][actual.y].Lados[ATRAS]);*/
    moveNode(direcciones[ADELANTE], &actual);
    return ADELANTE;
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
//    TX_BUFFER[0] = 'I';
  //  TX_BUFFER[1] = '\n';
   // HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    /*if (Map[x][y].visitado > 1) {
     EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
     direcciones[ATRAS]);
     intUartSend(5000);
     }*/
    if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
     Map[x][y].Lados[direcciones[ATRAS]] = 2;
     }
    last.x = actual.x;
    last.y = actual.y;
    moveNode(direcciones[IZQUIERDA], &actual);
    rotateAxis(IZQUIERDA, direcciones);
    return IZQUIERDA;
  } else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
   // TX_BUFFER[0] = 'D';
    //TX_BUFFER[1] = '\n';
    //HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);

    /*if (Map[x][y].visitado > 1) {
     EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
     direcciones[ATRAS]);
     intUartSend(5000);
     }*/
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
//     intUartSend(Map[x][y].Lados[direcciones[ATRAS]]);
     Map[x][y].Lados[direcciones[ATRAS]] = 2;
     }
    last.x = actual.x;
    last.y = actual.y;
    moveNode(direcciones[DERECHA], &actual);
    rotateAxis(DERECHA, direcciones);
    return DERECHA;
  } else {
    //TX_BUFFER[0] = 'O';
    //TX_BUFFER[1] = '\n';
    //HAL_UART_Transmit(&huart3, TX_BUFFER, 2, 100);
    return SearchAvailableNode(x, y);
  }

}

int SearchAvailableNode(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
    //Serial.println("Adelante1");

    /*if (Map[x][y].visitado > 1) {
     EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
     direcciones[ATRAS]);
     intUartSend(4000);
     }*/
    last.x = actual.x;
    last.y = actual.y;
    moveNode(direcciones[ADELANTE], &actual);

    return ADELANTE;
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
    //Serial.println("IZQUIERDA1");l
    //moveNode(IZQUIERDA);
    //rotateAxis(IZQUIERDA);
    /*if (Map[x][y].visitado > 1) {
     EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
     direcciones[ATRAS]);
     intUartSend(4000);
     }*/
    last.x = actual.x;
    last.y = actual.y;
    moveNode(direcciones[IZQUIERDA], &actual);

    rotateAxis(IZQUIERDA, direcciones);
    return IZQUIERDA;
  } else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
    //Serial.println("DERECHA1");
    /*if (Map[x][y].visitado > 1) {
     EliminateNode(&Map[actual.x][actual.y], &Map[last.x][last.y],
     direcciones[ATRAS]);
     intUartSend(4000);
     }*/
    last.x = actual.x;
    last.y = actual.y;
    moveNode(direcciones[DERECHA], &actual);
    rotateAxis(DERECHA, direcciones);
    return DERECHA;
  } else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
    last.x = actual.x;
    last.y = actual.y;
    //Map[x][y].Lados[direcciones[ATRAS]] = 2;
    moveNode(direcciones[ATRAS], &actual);

    rotateAxis(DERECHA, direcciones);
    rotateAxis(DERECHA, direcciones);
    return ATRAS;
  }
  return 0;
}
