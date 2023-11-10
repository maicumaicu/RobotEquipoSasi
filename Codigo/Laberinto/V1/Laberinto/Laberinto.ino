#include "Structs.h"
#include "Defines.h"
button btns[CANT_BTN];
motor Motors[2];
int sensores[cant_sensores];
int piso[2];

/* leer sensores 
   revisar mapeo
   leer encoders
   e implementar giroscopio*/
void setup() {
  // put your setup code here, to run once:
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(L1 , OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(INB1 , OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INA1 , OUTPUT);
  pinMode(INA2, OUTPUT);
  Serial.begin(9600);
   btns[0].PIN = B1;
  btns[0].estado = ESPERA;
  btns[0].flag = 0;
  btns[1].PIN = B2;
  btns[1].estado = ESPERA;
  btns[1].flag = 0;
  Motors[0].IN1 = INA1;
  Motors[0].IN2 = INA2;
  Motors[0].EN = PWM1;
  Motors[1].IN1 = INB1;
  Motors[1].IN2 = INB2;
  Motors[1].EN = PWM1;
}

void loop() {
  mainMachine();
  btnMachine(&btns[0]);
  btnMachine(&btns[1]);
  sensores[0] = lecturaSharp(1, S2_Pin);
  sensores[1] = lecturaSharp(1, S1_Pin);
  sensores[2] = lecturaSharp(1, S3_Pin);
}
