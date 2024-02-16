#include "Structs.h"
#include "Defines.h"
button btns[CANT_BTN];
motor Motors[2];
int sensores[cant_sensores];
int piso[1];
pdConfig pd[2];
int velocity;


void setup() {
  // put your setup code here, to run once:

  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(L1 , OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(PWMI, OUTPUT);
  pinMode(INB1 , OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(INA1 , OUTPUT);
  pinMode(INA2, OUTPUT);
  Serial.begin(9600);
  pd[0].KP = 5.5;
  pd[0].KD = 1;
  btns[0].PIN = B1;
  btns[0].estado = ESPERA;
  btns[0].flag = 0;
  btns[1].PIN = B2;
  btns[1].estado = ESPERA;
  btns[1].flag = 0;
  Motors[0].IN1 = INA1;
  Motors[0].IN2 = INA2;
  Motors[0].EN = PWMD;
  Motors[1].IN1 = INB1;
  Motors[1].IN2 = INB2;
  Motors[1].EN = PWMI;
}

void loop() {
  // put your main code here, to run repeatedly:
  mainMachine();
  btnMachine(&btns[0]);
  btnMachine(&btns[1]);
  sensores[0] = lecturaSharp(1, SD);
  sensores[1] = lecturaSharp(1, SC);
  sensores[2] = lecturaSharp(1, SI);
  piso[0] = lecturaCNY70(1, P1);
  Serial.println(lecturaCNY70(1, P1));
  //angularPID(IZQUIERDA, pd[0]);
  showModeNumber(piso[0]);
  //digitalWrite(2,HIGH);
  //setPowerMotor(IZQUIERDA,200);
  //setPowerMotor(DERECHA,200);
  //runMotor(ADELANTE, MOTOR_I);
  //digitalWrite(INB1,HIGH);
  //digitalWrite(INB2,LOW);

  //analogWrite(PWM1,power);
  //analogWrite(9, 200);
  //analogWrite(11, 200);
  //runMotor(ADELANTE, &Motors[MOT_IZQ]);
}

void showModeNumber(int number) {
  digitalWrite(2, number % 2);
  number /= 2;
  digitalWrite(3, number % 2);
  number /= 2;
}
