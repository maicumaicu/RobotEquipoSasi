#include "Structs.h"
#include "Defines.h"
button btns[CANT_BTN];
motor Motors[2];
int sensores[cant_sensores];
int piso[2];
int moveTime = 0;
int mode = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(INA1_Pin , OUTPUT);
  pinMode(INA2_Pin, OUTPUT);
  pinMode(EN1_Pin, OUTPUT);
  pinMode(INB1_Pin , OUTPUT);
  pinMode(INB2_Pin, OUTPUT);
  pinMode(EN2_Pin, OUTPUT);
  pinMode(B1_Pin, INPUT);
  pinMode(B2_Pin, INPUT);
  pinMode(L1_Pin , OUTPUT);
  pinMode(L2_Pin, OUTPUT);
  pinMode(L3_Pin , OUTPUT);
  pinMode(L4_Pin, OUTPUT);
  Serial.begin(9600);
  //Timer1.initialize(1000);
  //Timer1.attachInterrupt(tick);
  btns[0].PIN = B1_Pin;
  btns[0].estado = ESPERA;
  btns[0].flag = 0;
  btns[1].PIN = B2_Pin;
  btns[1].estado = ESPERA;
  btns[1].flag = 0;
  Motors[0].IN1 = INA1_Pin;
  Motors[0].IN2 = INA2_Pin;
  Motors[0].EN = EN1_Pin;
  Motors[1].IN1 = INB1_Pin;
  Motors[1].IN2 = INB2_Pin;
  Motors[1].EN = EN2_Pin;
}

void loop() {
  //showModeNumber(piso[0]*1+piso[1]*2+sensores[2]*4);
  //Serial.println(sensores[2]);
  btnMachine(&btns[0]);
  btnMachine(&btns[1]);
  sensores[0] = lecturaSharp(1, S2_Pin);
  sensores[1] = lecturaSharp(1, S3_Pin);
  sensores[2] = lecturaSharp(1, S1_Pin);
  piso[0] = lecturaCNY70(1, P1_Pin);
  piso[1] = lecturaCNY70(1, P2_Pin);
  mainMachine();
  
  //runMotor(ATRAS, Motors[DERECHA]);
  //setPowerMotor(200, DERECHA);
  //setPowerMotor(200, IZQUIERDA);
}
