
void initializeSharp() {
  pinMode(SHARP_D, INPUT);
  pinMode(SHARP_C, INPUT);
  pinMode(SHARP_I, INPUT);
}


/*int lecturaSensor(int n, int pin)
{
  long suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma = suma + analogRead(pin);
  }
  float adc = suma / n * 0.0008056;
  int distancia_cm = 12 * pow(adc, -1);
  Serial.print(pin);
  Serial.print(" distancia: ");
  Serial.println(distancia_cm);
  if (distancia_cm < 15) {
    return 1;
  } else {
    return 0;
  }
}*/

int lecturaSensor(int direccion) {
  return VisualMap[visual.x][visual.y].Lados[direccion];
}
