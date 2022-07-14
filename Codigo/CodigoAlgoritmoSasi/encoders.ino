void initializeEncoders() {
  pinMode(encoderPinA1, INPUT_PULLUP);
  pinMode(encoderPinB1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA1), isr_A1, CHANGE); //INTERRUPT FOR A
  attachInterrupt(digitalPinToInterrupt(encoderPinB1), isr_B1, CHANGE); //INTERRUPT FOR B

  pinMode(encoderPinA2, INPUT_PULLUP);
  pinMode(encoderPinB2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA2), isr_A2, CHANGE); //INTERRUPT FOR A
  attachInterrupt(digitalPinToInterrupt(encoderPinB2), isr_B2, CHANGE); //INTERRUPT FOR B
}


void isr_A1() {
  flag = true;
  if (digitalRead(encoderPinA1) == HIGH) {
    if (digitalRead(encoderPinB1) == LOW) {
      counterD  = counterD  - 1; //COUNTER CLOCK WISE
    }
    else {
      counterD  = counterD  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinB1) == HIGH) {
      counterD  = counterD  + 1; //CLOCK WISE
    }
    else {
      counterD  = counterD  - 1 ; //COUNTER CLOCK WISE
    }
  }
}

void isr_B1() {
  flag = true;
  if (digitalRead(encoderPinB1) == HIGH) {
    if (digitalRead(encoderPinA1) == HIGH) {
      counterD  = counterD  + 1;
    }
    else {
      counterD  = counterD  - 1;
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinA1) == LOW) {
      counterD  = counterD  + 1;
    }
    else {
      counterD  = counterD  - 1 ;
    }
  }
}

void isr_A2() {
  flag = true;
  if (digitalRead(encoderPinA2) == HIGH) {
    if (digitalRead(encoderPinB2) == LOW) {
      counterI  = counterI  - 1; //COUNTER CLOCK WISE
    }
    else {
      counterI  = counterI  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinB2) == HIGH) {
      counterI  = counterI  + 1; //CLOCK WISE
    }
    else {
      counterI  = counterI  - 1 ; //COUNTER CLOCK WISE
    }
  }

}

void isr_B2() {
  flag = true;
  if (digitalRead(encoderPinB2) == HIGH) {
    if (digitalRead(encoderPinA2) == HIGH) {
      counterI  = counterI  + 1;
    }
    else {
      counterI  = counterI  - 1;
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinA2) == LOW) {
      counterI  = counterI  + 1;
    }
    else {
      counterI  = counterI  - 1 ;
    }
  }

}

float calculoDistancia(int counter) {
  return (counter * 3.1416 * DIAMETRO_RUEDA / 12 / 100.35);
}
