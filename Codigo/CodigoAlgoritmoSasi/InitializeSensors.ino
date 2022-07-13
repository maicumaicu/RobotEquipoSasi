void initializeSharp(){
  pinMode(SHARP_D, INPUT);
  pinMode(SHARP_C, INPUT);
  pinMode(SHARP_I, INPUT);
}

void initializeLeds(){
  pinMode(LED_1, INPUT);
  pinMode(LED_2, INPUT);
}

void initializeMotors () {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}
