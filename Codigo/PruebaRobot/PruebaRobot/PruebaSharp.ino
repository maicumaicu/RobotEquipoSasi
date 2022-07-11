

void initializeSharp(){
  pinMode(SHARP_1, INPUT);
  pinMode(SHARP_2, INPUT);
  pinMode(SHARP_3, INPUT);
}

int lecturaSensor(int n, int pin)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(pin);
  }  
  float adc=suma/n * 0.0008056;
  float distancia_cm = 12*pow(adc, -1);
  return(distancia_cm);
}
