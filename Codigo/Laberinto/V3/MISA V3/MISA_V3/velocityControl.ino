int previousError, timePrev, elapsedTime;
int timeNow = 0;
char lado = 0;
void angularPID(pdConfig PD) {
  int error;
  if (count == WFI) {
    //intUartSend(0);
    error = lecturaSharpAnalog(1, SI) - DIST_IZQ;
    lado = IZQ;
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
  } else if(count == WFD) {
    //intUartSend(1);
    lado = DER;
    error = lecturaSharpAnalog(1, SD) - DIST_DER;
  } else if(count == MAP){
    if(lecturaSharpAnalog(1, SI) < DIST_IZQ){
      lado = IZQ;
       error = lecturaSharpAnalog(1, SI) - DIST_IZQ;
    }else if(lecturaSharpAnalog(1, SD) < DIST_DER) {
      lado = DER;
      error = lecturaSharpAnalog(1, SD) - DIST_DER;
    }else{
      error = getTurnAngle() - offset;
      lado = DER;
    }
  }
  /*if (Sensors[2] < maxDistance[0]) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
    } else {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
    }*/
  timePrev = timeNow;
  timeNow = millis();
  elapsedTime = (timeNow - timePrev) / 1000;
  float pidD = PD.KD * ((error - previousError) / elapsedTime);
  float pidP = PD.KP * error;
  float pid = pidP + pidD;

  if (pid > 2000) {
    //intUartSend(1);
    pid = 2000;
  }
  if (pid < -2000) {
    //intUartSend(0);
    pid = -2000;
  }
  int motLeft, motRight;
  if (lado  == IZQ) {
    motLeft = velocity + pid;
    motRight = velocity - pid;
  }
  else if(lado == DER) {
    motLeft = velocity - pid;
    motRight = velocity + pid;
  }
  //Serial.println(motLeft);
  
  previousError = error;
  motRight = constrain(motRight, -1000, 1000);
  motLeft = constrain(motLeft, -1000, 1000);

  motRight = map(motRight, -1000, 1000, 0, MAX_SPEED * 2);
  motLeft = map(motLeft, -1000, 1000, 0, MAX_SPEED * 2);

  //Serial.println(motRight);
  analogWrite(9, motLeft);
  analogWrite(11, motRight);
}
