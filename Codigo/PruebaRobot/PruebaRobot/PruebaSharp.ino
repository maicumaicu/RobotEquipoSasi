

void initializeSharp() {
  pinMode(SHARP_1, INPUT);
  pinMode(SHARP_2, INPUT);
  pinMode(SHARP_3, INPUT);
}

int lecturaSensor(int n, int pin)
{
  long suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma = suma + analogRead(pin);
  }

  float adc = suma / n;
  float distancia_cm = 29.988 * pow(map(adc, 0, 4095, 0, 5000)/1000.0, -1.173);
  return (distancia_cm);
}
