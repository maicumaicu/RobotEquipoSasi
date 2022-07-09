

void initializeSharp(){
  pinMode(SHARP_1, INPUT);
  pinMode(SHARP_2, INPUT);
  pinMode(SHARP_3, INPUT);
}

float distancia(int n, int pin)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(pin);
  }  
  float adc=suma/n;
  float distancia_cm = 17569.7 * pow(adc, -1.2062);
  return(distancia_cm);
}

float lecturaSensor(int pin){
  long tiempo=millis(); //tiempo antes de iniciar la lectura
  int D_cm = distancia(20, pin); //lectura de distancia
  tiempo=millis()-tiempo; //milisegundos que duró la lectura
  Serial.print("Tiempo de lectura: ");
  Serial.print(tiempo); 
  Serial.print("ms  Distancia: ");
  Serial.print(D_cm);
  Serial.println("  cm");
  return D_cm;
}
