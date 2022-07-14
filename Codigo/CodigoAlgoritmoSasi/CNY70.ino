int lecturaCNY70(int n, int pin){
  long suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma = suma + analogRead(pin);
  }
  return (suma / n);
}
