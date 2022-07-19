
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
  return distancia_cm;
}

int lecturaSensor(int direccion) {
  return VisualMap[visual.x][visual.y].Lados[direccion];
}
