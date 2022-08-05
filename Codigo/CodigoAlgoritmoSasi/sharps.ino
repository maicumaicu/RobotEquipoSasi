
void initializeSharp() {
  pinMode(SHARP_D, INPUT);
  pinMode(SHARP_C, INPUT);
  pinMode(SHARP_I, INPUT);
}


float lecSensor(int n, int pin)
{
  long suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma = suma + analogRead(pin);
  }
  float adc = suma / n;
  float volts = adc * 0.0008056640; // value from sensor * (5/1024)
  int distance = 13 * pow(volts, -1);
  //SerialBT.println(distancia_cm);
  return distance;
}

int wallDetector(int n, int pin) {
  float valor = lecSensor(n, pin);
  if (valor > 15) {
    return 0;
  } else {
    return 1;
  }
}

int lecturaSensor(int direccion) {
  switch (direccion) {
    case ADELANTE:
      return wallDetector(20, SHARP_C);
      break;
    case DERECHA:
      return wallDetector(20, SHARP_D);
      break;
    case IZQUIERDA:
      return wallDetector(20, SHARP_I);
      break;
    case ATRAS:
      return 0;
      break;
  }
}
