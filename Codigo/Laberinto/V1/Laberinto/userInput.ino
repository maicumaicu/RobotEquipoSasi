int lecturaBtn,ticks;

void showModeNumber(int number) {
  digitalWrite(2,number % 2);
  number /= 2;
  digitalWrite(3,number % 2);
  number /= 2; 
}

void btnMachine(button* btn) {
  switch (btn->estado) {
  case ESPERA:
    (*btn).flag = 0;
    lecturaBtn = digitalRead((*btn).PIN);
    if (lecturaBtn == 0) {
      ticks = millis();
      (*btn).estado = CONFIRMACION;
    }
    break;

  case CONFIRMACION:
    lecturaBtn = digitalRead((*btn).PIN);
    if (lecturaBtn == 0 && millis() >= ticks + TICKS_BTN) {

      (*btn).estado = LIBERACION;
    }

    if (lecturaBtn == 1 && ticks < TICKS_BTN) {

      (*btn).estado = ESPERA;
    }
    break;

  case LIBERACION:
    lecturaBtn = digitalRead((*btn).PIN);
    if (lecturaBtn == 1) {
      (*btn).flag = 1;
      (*btn).estado = ESPERA;
    }
    break;
  }
}
 
