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
      runMotor(ATRAS, Motors[DERECHA]);
      runMotor(ADELANTE, Motors[IZQUIERDA]);
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
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        runMotor(ADELANTE, Motors[IZQUIERDA]);
        if (posicionLinea == -1) {
          targetTracking(posicionObjetivo);
        } else {
          if (posicionLinea > 0) {
            digitalWrite(8, HIGH);
            digitalWrite(9, LOW);
            runMotor(ATRAS, Motors[IZQUIERDA]);
          }else{
            digitalWrite(8, LOW);
            digitalWrite(9, HIGH);
            runMotor(ADELANTE, Motors[IZQUIERDA]);
          }
          lineTracking(posicionLinea);
        }
      } else {
        showModeNumber(1);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        runMotor(ATRAS, Motors[IZQUIERDA]);
        lineTracking(posicionLinea);
      }
      break;
  }
}
