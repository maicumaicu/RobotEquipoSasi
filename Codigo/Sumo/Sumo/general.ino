int count = 0;
int mainState;
int angulo;

void mainMachine() {
  switch (mainState) {
    case INIT:

      if (btns[0].flag == 1) {
        count++;
      }
      if (count >= 4 || count <= 0) {
        count = 0;
      }
      showModeNumber(count);

      if (btns[1].flag == 1) {
        mainState = SECUENCIA_INICIO;
        showModeNumber(0);
        showModeNumber(3);
        delay(5000);
      }
      break;
    case SECUENCIA_INICIO:
      showModeNumber(1);
      angulo = (180 / 4) * count;
      runMotor(ADELANTE, &Motors[DERECHA]);
      runMotor(ATRAS, &Motors[IZQUIERDA]);
      setPowerMotor(200, DERECHA);
      setPowerMotor(200, IZQUIERDA);
      delay(count * TIEMPO_VUELTA);
      setPowerMotor(0, DERECHA);
      setPowerMotor(0, IZQUIERDA);
      mainState = MAIN;
      break;
    case MAIN:
      int posicionLinea = linePosition(piso);
      int posicionObjetivo = targetPosition(sensores);
      if (posicionLinea != 0) {
        runMotor(ADELANTE, &Motors[DERECHA]);
        runMotor(ADELANTE, &Motors[IZQUIERDA]);
        if (posicionLinea == -1) {
          targetTracking(posicionObjetivo);
        } else {
          if (posicionLinea > 0) {
            runMotor(ATRAS, &Motors[IZQUIERDA]);
            runMotor(ATRAS, &Motors[IZQUIERDA]);
          } else {
            runMotor(ADELANTE, &Motors[IZQUIERDA]);
            runMotor(ADELANTE, &Motors[IZQUIERDA]);
          }
          lineTracking(posicionLinea);
        }
      } else {
        showModeNumber(1);
        runMotor(ATRAS, &Motors[DERECHA]);
        runMotor(ATRAS, &Motors[IZQUIERDA]);
        lineTracking(posicionLinea);
      }
      /* if (piso[0] == BLANCO && piso[1] == BLANCO) {
          //showModeNumber(0);
         digitalWrite(8, LOW);
         digitalWrite(9, HIGH);
         runMotor(ATRAS, Motors[IZQUIERDA]);
         setPowerMotor(40, IZQUIERDA);
         setPowerMotor(250, DERECHA);
         delay(400);
         }
        } else if (piso[1] == BLANCO) {

         digitalWrite(8, LOW);
         digitalWrite(9, HIGH);
         runMotor(ATRAS, Motors[IZQUIERDA]);
         setPowerMotor(250, IZQUIERDA);
         setPowerMotor(40, DERECHA);
         delay(400);
        }
        else if (piso[0] == BLANCO) {

          digitalWrite(8, LOW);
         digitalWrite(9, HIGH);
         runMotor(ATRAS, Motors[IZQUIERDA]);
         setPowerMotor(40, IZQUIERDA);
         setPowerMotor(250, DERECHA);
         delay(400);
        }else{
         if (sensores[1] == 1) {
           showModeNumber(1);
           digitalWrite(8, HIGH);
           digitalWrite(9, LOW);
           runMotor(ADELANTE, Motors[IZQUIERDA]);
           setPowerMotor(250, IZQUIERDA);
           setPowerMotor(250, DERECHA);
         }
         else if (sensores[2] == 1) {
           showModeNumber(3);
           digitalWrite(8, HIGH);
           digitalWrite(9, LOW);
           runMotor(ATRAS, Motors[IZQUIERDA]);
           setPowerMotor(250, IZQUIERDA);
           setPowerMotor(40, DERECHA);
         } else if  (sensores[0] == 1) {
           showModeNumber(2);
           digitalWrite(8, LOW);
           digitalWrite(9, HIGH);
           runMotor(ADELANTE, Motors[IZQUIERDA]);
           setPowerMotor(40, IZQUIERDA);
           setPowerMotor(250, DERECHA);
         }else{
            showModeNumber(0);
            digitalWrite(8, HIGH);
           digitalWrite(9, LOW);
           runMotor(ADELANTE, Motors[IZQUIERDA]);
           setPowerMotor(120, IZQUIERDA);
           setPowerMotor(120, DERECHA);
        }
        break;*/
  }
}
