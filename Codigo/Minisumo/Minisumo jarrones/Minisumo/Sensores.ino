int lecturaCNY70(int n,int pin) {
  long suma = 0;
  for (int i = 0; i < n; i++) {
    suma = suma + analogRead(pin);
  }
  int adc = (suma / n);
  if (adc < 300) {
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
