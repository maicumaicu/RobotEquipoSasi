 int mainState = 0;
 int lado = 0;
void mainMachine(){
  switch(mainState){
    case INIT:
    if(btns[0].flag == 1){
      lado = IZQUIERDA;
      velocity = 1000;
      mainState = RUN;
      Serial.println(mainState);
    }
    if(btns[1].flag == 1){
      lado = DERECHA;
      velocity = 1000;
      mainState = RUN;
      Serial.println(mainState);
    }
    break;
    case RUN:
    //Serial.println(lado);
    
    runMachine(lado);
    break;
  }
}
