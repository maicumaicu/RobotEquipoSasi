void runMotor(int dir, motor* motor) {
  switch (dir) {
  case ADELANTE:
    digitalWrite(motor->IN1,HIGH);
    digitalWrite(motor->IN2,LOW);
    break;
  case ATRAS:
    digitalWrite(motor->IN1,LOW);
    digitalWrite(motor->IN2,HIGH);
    break;
  case OFF:
    digitalWrite(motor->IN1,HIGH);
    digitalWrite(motor->IN2,HIGH);
    break;
  }
}
void setPowerMotor(int power, int motor) {
  if (motor == IZQUIERDA) {
    analogWrite(PWM2_Pin,power);
  } else {
    analogWrite(PWM1_Pin,power);
  }
}
