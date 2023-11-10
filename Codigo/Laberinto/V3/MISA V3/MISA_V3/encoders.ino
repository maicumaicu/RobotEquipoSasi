void initializeEncoders() {
  pinMode(MA1, INPUT_PULLUP);
  pinMode(MB1, INPUT_PULLUP);
   PcInt::attachInterrupt(MA1, isr_A1, CHANGE); //INTERRUPT FOR A
   PcInt::attachInterrupt(MB1, isr_B1, CHANGE); //INTERRUPT FOR B

  pinMode(MA2, INPUT_PULLUP);
  pinMode(MB2, INPUT_PULLUP);
   PcInt::attachInterrupt(MA2, isr_A2, CHANGE); //INTERRUPT FOR A
   PcInt::attachInterrupt(MB2, isr_B2, CHANGE); //INTERRUPT FOR B
}


void isr_A1() {
  flag = true;
  if (digitalRead(MA1) == HIGH) {
    if (digitalRead(MB1) == LOW) {
      counterD  = counterD  - 1;
      //Serial.print("RESTO");//COUNTER CLOCK WISE
    }
    else {
      counterD  = counterD  + 1; 
      //Serial.print("SUMO");//CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(MB1) == HIGH) {
      counterD  = counterD  + 1; 
      // Serial.print("SUMO");//CLOCK WISE
    }
    else {
      counterD  = counterD  - 1 ;
       //Serial.print("RESTO");//COUNTER CLOCK WISE
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
      //Serial.println("RESTO");
      counterI  = counterI  - 1; //COUNTER CLOCK WISE
    }
    else {
      //Serial.println("SUMO");
      counterI  = counterI  + 1; //CLOCK WISE
    }
  }
  else { //IF PIN A IS LOW
    if (digitalRead(MB2) == HIGH) {
      //Serial.println("SUMO");
      counterI  = counterI  + 1; //CLOCK WISE
    }
    else {
      //Serial.println("RESTO");
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

float calcularDistancia(int counter) {
  return (counter * 2.51 / 10);
}
