
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
