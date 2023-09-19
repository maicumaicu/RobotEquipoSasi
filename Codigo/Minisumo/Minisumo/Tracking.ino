float pid, elapsedTime, pidP, pidD, errorP, timeNowP, timePrevP, previousErrorP;
int motLeft, motRight;
int velocity = 1000;
float KPT = 1;
float KDT = 1;
float KPL = 1;
float KDL = 1;
int xSpeed;
/*
int targetPosition(int *mediciones) {
  return (mediciones[0] + mediciones[1] + mediciones[2]) != 0 ?
         ((-1000 * mediciones[0] + 0 * mediciones[1] + 1000 * mediciones[2])
          / (mediciones[0] + mediciones[1] + mediciones[2]
            )) :
         -1;
}

int linePosition(int *mediciones) {
  return (mediciones[0] + mediciones[1])
         != 0 ?
         ((-1000 * mediciones[0] + 1000 * mediciones[1])) :
         -1;
}

void targetTracking(int position) {
  errorP = position;
  timePrevP = timeNowP;
  timeNowP = millis();
  elapsedTime = (timeNowP - timePrevP) / 1000;
  pidD = KDT * ((errorP - previousErrorP) / elapsedTime);
  pidP = KPT * errorP;
  pid = pidP + pidD;
  if (pid > velocity) {
    //intUartSend(1);
    pid = velocity;
  }
  if (pid < -velocity) {
    //intUartSend(0);
    pid = -velocity;
  }
  //Serial.println(pid);
  motLeft = velocity + pid;
  motRight = velocity - pid;

  if (motLeft < -1000) {
    motLeft = -1000;
  }
  if (motRight < -1000) {
    motRight = -1000;
  }

  previousErrorP = errorP;
  motRight = constrain(motRight, -1000, 1000);
  motLeft = constrain(motLeft, -1000, 1000);

  motRight = map(motRight, -1000, 1000, MINVELOCITY, MAXVELOCITY);
  motLeft = map(motLeft, -1000, 1000, MINVELOCITY, MAXVELOCITY);

  if (motRight < MINVELOCITY) {
    motRight = MINVELOCITY;
  }

  if (motLeft < MINVELOCITY) {
    motLeft = MINVELOCITY;
  }
  if (position != -1) {
    //setPowerMotor(motRight, DERECHA);
    analogWrite(EN2_Pin,motRight);
    setPowerMotor(motLeft, IZQUIERDA);
  } else {
    //setPowerMotor(motRight, 130);
    analogWrite(EN2_Pin,130);
    setPowerMotor(motLeft, 100);
  }
}
void lineTracking(int position) {

  errorP = position;
  timePrevP = timeNowP;
  timeNowP = millis();
  elapsedTime = (timeNowP - timePrevP) / 1000;
  pidD = KDL * ((errorP - previousErrorP) / elapsedTime);
  pidP = KPL * errorP;
  pid = pidP + pidD;
  if (pid > velocity) {
    //intUartSend(1);
    pid = velocity;
  }
  if (pid < -velocity) {
    //intUartSend(0);
    pid = -velocity;
  }
  motLeft = velocity - pid;
  motRight = velocity + pid;
  if (motLeft < -1000) {
    motLeft = -1000;
  }
  if (motRight < -1000) {
    motRight = -1000;
  }

  previousErrorP = errorP;
  motRight = constrain(motRight, -1000, 1000);
  motLeft = constrain(motLeft, -1000, 1000);

  motRight = map(motRight, -1000, 1000, MINVELOCITY, MAXVELOCITY);
  motLeft = map(motLeft, -1000, 1000, MINVELOCITY, MAXVELOCITY);

  if (motRight < MINVELOCITY) {
    motRight = MINVELOCITY;
  }

  if (motLeft < MINVELOCITY) {
    motLeft = MINVELOCITY;
  }
  if (position != 0) {
    
    analogWrite(EN2_Pin,motRight);
    setPowerMotor(motLeft, IZQUIERDA);
  } else {
    analogWrite(EN2_Pin,230);
    setPowerMotor(motLeft, 200);
  }

}*/
