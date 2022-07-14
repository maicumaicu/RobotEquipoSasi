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
      counter1  = counter1  - 1; //COUNTER CLOCK WISE
    }
    else {
      counter1  = counter1  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinB1) == HIGH) {
      counter1  = counter1  + 1; //CLOCK WISE
    }
    else {
      counter1  = counter1  - 1 ; //COUNTER CLOCK WISE
    }
  }

}

void isr_B1() {
  flag = true;
  if (digitalRead(encoderPinB1) == HIGH) {
    if (digitalRead(encoderPinA1) == HIGH) {
      counter1  = counter1  + 1;
    }
    else {
      counter1  = counter1  - 1;
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinA1) == LOW) {
      counter1  = counter1  + 1;
    }
    else {
      counter1  = counter1  - 1 ;
    }
  }
}

void isr_A2() {
  flag = true;
  if (digitalRead(encoderPinA2) == HIGH) {
    if (digitalRead(encoderPinB2) == LOW) {
      counter2  = counter2  - 1; //COUNTER CLOCK WISE
    }
    else {
      counter2  = counter2  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinB2) == HIGH) {
      counter2  = counter2  + 1; //CLOCK WISE
    }
    else {
      counter2  = counter2  - 1 ; //COUNTER CLOCK WISE
    }
  }

}

void isr_B2() {
  flag = true;
  if (digitalRead(encoderPinB2) == HIGH) {
    if (digitalRead(encoderPinA2) == HIGH) {
      counter2  = counter2  + 1;
    }
    else {
      counter2  = counter2  - 1;
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(encoderPinA2) == LOW) {
      counter2  = counter2  + 1;
    }
    else {
      counter2  = counter2  - 1 ;
    }
  }

}

int calculoDistancia(int counter) {
  return counter * DIAMETRO_RUEDA * 3.1416 / 2 / 100;
}
