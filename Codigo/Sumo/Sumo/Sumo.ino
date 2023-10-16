#include "Structs.h"
#include "Defines.h"
#include <ShiftIn.h>
ShiftIn<1> shift;
button btns[CANT_BTN];
motor Motors[2];
int sensores[cant_sensores];
int piso[5];

void setup() {
  // put your setup code here, to run once:
  pinMode(INA1_Pin, OUTPUT);
  pinMode(INA2_Pin, OUTPUT);
  pinMode(PWM1_Pin, OUTPUT);
  pinMode(PWM2_Pin, OUTPUT);
  pinMode(EN1_Pin, OUTPUT);
  pinMode(INB1_Pin , OUTPUT);
  pinMode(INB2_Pin, OUTPUT);
  pinMode(B1_Pin, INPUT);
  pinMode(B2_Pin, INPUT);
  pinMode(L1_Pin , OUTPUT);
  pinMode(L2_Pin, OUTPUT);
  Serial.begin(9600);
  btns[0].PIN = B1_Pin;
  btns[0].estado = ESPERA;
  btns[0].flag = 0;
  btns[1].PIN = B2_Pin;
  btns[1].estado = ESPERA;
  btns[1].flag = 0;
  Motors[0].IN1 = INA1_Pin;
  Motors[0].IN2 = INA2_Pin;
  Motors[0].EN = PWM1_Pin;
  Motors[1].IN1 = INB1_Pin;
  Motors[1].IN2 = INB2_Pin;
  Motors[1].EN = PWM2_Pin;
  sensores[0] = 0;
  sensores[1] = 0;
  sensores[2] = 0;
  sensores[3] = 0;
  sensores[4] = 0;
  shift.begin(LP_Pin, CEP_Pin, S_Pin, CP_Pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  btnMachine(&btns[0]);
  btnMachine(&btns[1]);
  // hacer la lectura de sensores con el shift register
  if (shift.update()) {
    for(int i = 0; i < shift.getDataWidth(); i++){
      sensores[i] =  shift.state(i);
      Serial.println(sensores[i]);
      digitalWrite(L1_Pin, sensores[0]);
    }
  }
  piso[0] = lecturaCNY70(1, P1_Pin);
  piso[1] = lecturaCNY70(1, P2_Pin);
  piso[2] = lecturaCNY70(1, P3_Pin);
  piso[3] = lecturaCNY70(1, P4_Pin);
  piso[4] = lecturaCNY70(1, P5_Pin);
  mainMachine();
}
