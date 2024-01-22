-



int lecBtn(int pin){
  if(analogRead(pin) < 500){
    return 0;
  }else{
    return 1;
  }
}

void btnMachine(button* btn) {
  switch (btn->estado) {
  case ESPERA:
    (*btn).flag = 0;
    lecturaBtn = lecBtn((*btn).PIN);
    if (lecturaBtn == 0) {
      ticks = millis();
      (*btn).estado = CONFIRMACION;
    }
    break;

  case CONFIRMACION:
    lecturaBtn = lecBtn((*btn).PIN);
    if (lecturaBtn == 0 && millis() >= ticks + TICKS_BTN) {
      Serial.println("hola");
      (*btn).estado = LIBERACION;
    }

    if (lecturaBtn == 1 && ticks < TICKS_BTN) {

      (*btn).estado = ESPERA;
    }
    break;

  case LIBERACION:
    lecturaBtn = lecBtn((*btn).PIN);
    if (lecturaBtn == 1) {
      (*btn).flag = 1;
      (*btn).estado = ESPERA;
    }
    break;
  }
}
