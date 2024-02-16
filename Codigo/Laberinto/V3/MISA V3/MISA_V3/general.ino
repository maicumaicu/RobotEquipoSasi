int mainState = 0;
int count = 0;
int finished = 0;
int finishFlag = 0;
void mainMachine() {
  switch (mainState) {
    case INIT:
      actual.x = ALTO;
      actual.y = ANCHO;
      resetAxis(direcciones);
      movimientoFlag = 0;
      finishFlag = 0;
      if (btns[0].flag == 1) {
        count++;
        showModeNumber(2);
      }
      if (count >= 4 || count <= 0) {
        count = 0;
      }
      showModeNumber(count);

      if (btns[1].flag == 1) {
        velocity = 1000;
        mainState = RUN;
        showModeNumber(1);
        

      }
      break;
    case R:
      //Serial.println(lado);
      showModeNumber(count+1);
      runMachine();
      /*if(finished == 1){
        mainState = INIT;
      }*/
      break;
  }
}
