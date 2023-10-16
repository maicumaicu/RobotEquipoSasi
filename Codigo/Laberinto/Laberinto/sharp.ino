int wallDetector(int n, int d, float maxDis[3]) {
  switch (d) {
  case ADELANTE:
    if (n < maxDis[0]) {
      return 1;
    } else {

      return 0;
    }
    break;

  case IZQUIERDA:
    if (n < maxDis[1]) {
      return 1;
    } else {
      return 0;
    }
    break;
  case DERECHA:
    if (n < maxDis[2]) {
      return 1;
    } else {
      return 0;
    }
    break;
  default:
    return 0;
    break;
  }
}

float lecturaSensor(int direccion, int values[4], float maxDis[3]) {
  switch (direccion) {
  case ADELANTE:
    return wallDetector(values[2], direccion, maxDis);
    break;
  case DERECHA:
    return wallDetector(values[1], direccion, maxDis);
    break;
  case IZQUIERDA:
    return wallDetector(values[3], direccion, maxDis);
    break;
  case ATRAS:
    return 0;
    break;
  }
  return 15;
}


int lecturaCNY70(int n, int pin) {
long suma = 0;
  for (int i = 0; i < n; i++) {
    suma = suma + analogRead(pin);
  }
  int adc = (suma / n);
  if (adc < 200) {
    return BLANCO;
  } else {
    return NEGRO;
  }
}

int lecturaSharp(int n,int pin) {
  long suma = 0;
  for (int i = 0; i < n; i++) {
    suma = suma + analogRead(pin);
  }
  int adc = (suma / n);
  if (adc < 200) {
    return BLANCO;
  } else {
    return NEGRO;
  }
}
