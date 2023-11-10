void initializeEncoders() {
  pinMode(MA1, INPUT_PULLUP);
  pinMode(MB1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MA1), isr_A1, CHANGE); //INTERRUPT FOR A
  attachInterrupt(digitalPinToInterrupt(MB1), isr_B1, CHANGE); //INTERRUPT FOR B

  pinMode(MA2, INPUT_PULLUP);
  pinMode(MB2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MA2), isr_A2, CHANGE); //INTERRUPT FOR A
  attachInterrupt(digitalPinToInterrupt(MB2), isr_B2, CHANGE); //INTERRUPT FOR B
}


void isr_A1() {
  flag = true;
  if (digitalRead(MA1) == HIGH) {
    if (digitalRead(MB1) == LOW) {
      counterD  = counterD  - 1; //COUNTER CLOCK WISE
    }
    else {
      counterD  = counterD  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(MB1) == HIGH) {
      counterD  = counterD  + 1; //CLOCK WISE
    }
    else {
      counterD  = counterD  - 1 ; //COUNTER CLOCK WISE
    }
  }
}

void isr_B1() {
  flag = true;
  if (digitalRead(MB1) == HIGH) {
    if (digitalRead(MA1) == HIGH) {
      counterD  = counterD  + 1;
    }
    else {
      counterD  = counterD  - 1;
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(MA1) == LOW) {
      counterD  = counterD  + 1;
    }
    else {
      counterD  = counterD  - 1 ;
    }
  }
}

void isr_A2() {
  flag = true;
  if (digitalRead(MA2) == HIGH) {
    if (digitalRead(MB2) == LOW) {
      counterI  = counterI  - 1; //COUNTER CLOCK WISE
    }
    else {
      counterI  = counterI  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(MB2) == HIGH) {
      counterI  = counterI  + 1; //CLOCK WISE
    }
    else {
      counterI  = counterI  - 1 ; //COUNTER CLOCK WISE
    }
  }

}

void isr_B2() {
  flag = true;
  if (digitalRead(MB2) == HIGH) {
    if (digitalRead(MA2) == HIGH) {
      counterI  = counterI  + 1;
    }
    else {
      counterI  = counterI  - 1;
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(MA2) == LOW) {
      counterI  = counterI  + 1;
    }
    else {
      counterI  = counterI  - 1 ;
    }
  }

}
