
void initializeSharp() {
  pinMode(SHARP_D, INPUT);
  pinMode(SHARP_C, INPUT);
  pinMode(SHARP_I, INPUT);
}


int lecSensor(int n, int pin)
{
  long suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma = suma + analogRead(pin);
  }
  float adc = suma / n;
  float distancia_cm = 29.988 * pow(map(adc, 0, 4095, 0, 5000) / 1000.0, -1.173);
  SerialBT.println(distancia_cm);
  return distancia_cm;
}

int wallDetector(int n, int pin) {
  int valor = lecSensor(n, pin);
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
