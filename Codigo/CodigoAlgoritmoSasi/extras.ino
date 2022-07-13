void ledOn(int pin) {
  analogWrite(pin, 20);
}

void ledOff(int pin) {
  analogWrite(pin, 0);
}
