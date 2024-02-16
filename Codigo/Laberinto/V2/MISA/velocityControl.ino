int error, previousError, timePrev, elapsedTime, motLeft, motRight;
float pidD, pidP, pid;
int timeNow = 0;
void angularPID(int lado, pdConfig PD) {
  if (lado == IZQUIERDA) {
    //intUartSend(0);
    error = lecturaSharpAnalog(1, SI) - DIST_IZQ;

    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
  } else {
    //intUartSend(1);
    error = lecturaSharpAnalog(1, SD) - DIST_DER;
  }
  /*if (Sensors[2] < maxDistance[0]) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
    } else {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
    }*/
  timePrev = timeNow;
  timeNow = millis();
  elapsedTime = (timeNow - timePrev) / 1000;
  pidD = PD.KD * ((error - previousError) / elapsedTime);
  pidP = PD.KP * error;
  pid = pidP + pidD;

  if (pid > 2000) {
    //intUartSend(1);
    pid = 2000;
  }
  if (pid < -2000) {
    //intUartSend(0);
    pid = -2000;
  }
  if (lado == IZQUIERDA) {
    motLeft = velocity + pid;
    motRight = velocity - pid;
  }
  else {
    motLeft = velocity - pid;
    motRight = velocity + pid;
  }
  //Serial.println(motLeft);

  previousError = error;
  motRight = constrain(motRight, -1000, 1000);
  motLeft = constrain(motLeft, -1000, 1000);

  motRight = map(motRight, -1000, 1000, 0, MAX_SPEED * 2);
  motLeft = map(motLeft, -1000, 1000, 0, MAX_SPEED * 2);

  Serial.println(motRight);
  analogWrite(9, motLeft);
  analogWrite(11, motRight);
}
