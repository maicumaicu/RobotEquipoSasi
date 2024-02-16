int robotState = 0;
int movimiento;
void runMachine() {
  /*if (movimientoFlag == 0) {
    Serial.println(IZQ);
    movementMachine(IZQ);
    } else {
    runMotor(OFF, &Motors[MOT_IZQ]);
    runMotor(OFF, &Motors[MOT_DER]);
    Serial.println("1");
    analogWrite(9, 0);
    analogWrite(11, 0);
    }*/
  
  if (count == MAP) {
    
    if (finishFlag == 0) {
      
      robotMachine();

    } else {
      showModeNumber(3);
      actual.x = ALTO;
      actual.y = ANCHO;
      //visual.x = 0;
      //visual.y = 0;
      finishFlag = 0;
      resetAxis(direcciones);
      //PrintMap();
      count = RESOLUTION;
    }
  }
  else if (count == RESOLUTION) {
    if (Map[actual.x][actual.y].final == 0) {
      //addDirection(actual.x, actual.y);
    } else {
      //directions = optimizeDirections(directions);
      //SerialBT.println(directions);
      // UploadRun(directions);
      //directions[directionsSize] = 'o';
      //Flash_Write_Data(0x0801FC00, (uint32_t*) directions, 25);
      finished = 1;
    }
  }
  else if (count == RUN) {
    //    runDirections(string);
  }
  else if (count == WFI) {
    if (piso[0] == NEGRO) {
      if (sensores[CENTRO] == PARED) {
        if (sensores[IZQUIERDA] == LIBRE) {
          //izquierda 90
          showModeNumber(0);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ);
          showModeNumber(0);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        } else if (sensores[DERECHA] == LIBRE) {
          showModeNumber(1);
          runMotor(ADELANTE, &Motors[MOT_IZQ]);
          runMotor(ATRAS, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_DER);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        } else {
          //izquierda 180
          showModeNumber(2);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ * 2);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        }
      } else {
        //showModeNumber(3);
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        angularPID( pd[0]);

      }
    } else {
      showModeNumber(3);
      runMotor(OFF, &Motors[MOT_IZQ]);
      runMotor(OFF, &Motors[MOT_DER]);
      analogWrite(9, 0);
      analogWrite(11, 0);
    }
  } else if (count == WFD) {
    if (piso[0] == NEGRO) {
      if (sensores[CENTRO] == PARED) {
        if (sensores[DERECHA] == LIBRE) {
          showModeNumber(1);
          runMotor(ADELANTE, &Motors[MOT_IZQ]);
          runMotor(ATRAS, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_DER);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        }
        else if (sensores[IZQUIERDA] == LIBRE) {
          //izquierda 90
          showModeNumber(0);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ);
          showModeNumber(0);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        } else {
          //izquierda 180
          showModeNumber(2);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ * 2);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        }
      } else {

        //showModeNumber(3);
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        angularPID( pd[0]);

      }
    } else {
      showModeNumber(3);
      runMotor(OFF, &Motors[MOT_IZQ]);
      runMotor(OFF, &Motors[MOT_DER]);
      analogWrite(9, 0);
      analogWrite(11, 0);
    }
  }
}


void robotMachine() {
  switch (robotState) {
    case READING:
      Map[actual.x][actual.y].visitado++;

      if (Map[actual.x][actual.y].visitado == 1) {
        runMotor(OFF, &Motors[MOT_IZQ]);
        runMotor(OFF, &Motors[MOT_DER]);
        CreateNode(&Map[actual.x][actual.y]);
        
        if (q == 1) {
          Map[actual.x][actual.y].Lados[direcciones[ATR]] = 1;
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
      */    //Sensors[0];
      if (piso[0] == BLANCO) {
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
      Serial.println(Map[actual.x][actual.y].Lados[direcciones[IZQ]]);
      movimientoFlag = 0;
      //ticksNow = millis();
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
