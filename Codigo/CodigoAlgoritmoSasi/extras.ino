
void initializeLeds() {
  pinMode(LED_1, INPUT);
  pinMode(LED_2, INPUT);
}


void ledOn(int pin) {
  analogWrite(pin, 20);
}

void ledOff(int pin) {
  analogWrite(pin, 0);
}
int calculoDistancia(int counter) {
  return counter * DIAMETRO_RUEDA * 3.1416 / 2 / 100;
}
