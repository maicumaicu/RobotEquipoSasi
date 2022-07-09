#include <analogWrite.h>

#define AIN1 18
#define AIN2 19
#define PWMA 14
#define BIN2 32
#define BIN1 17
#define PWMB 12
#define MOTOR_A 0
#define MOTOR_B 1
#define ADELANTE 0
#define ATRAS 1

#define SHARP_1 26
#define SHARP_2 25
#define SHARP_3 33


const int freq = 5000;
const int motorAChannel = 0;
const int motorBChannel = 1;
const int sharp1Channel = 2;
const int sharp2Channel = 3;
const int sharp3Channel = 4;
const int resolution = 8;

void initializeAnalog() {
  ledcSetup(motorAChannel, freq, resolution);
  ledcSetup(motorBChannel, freq, resolution);
  ledcSetup(sharp1Channel, freq, resolution);
  ledcSetup(sharp2Channel, freq, resolution);
  ledcSetup(sharp3Channel, freq, resolution);

  ledcAttachPin(PWMA, motorAChannel);
  ledcAttachPin(PWMB, motorBChannel);
  ledcAttachPin(SHARP_1, sharp1Channel);
  ledcAttachPin(SHARP_2, sharp2Channel);
  ledcAttachPin(SHARP_3, sharp3Channel);
}

void setup() {
  // put your setup code here, to run once:
  //initializeAnalog();
  initializeSharp();
  initializeMotors();

}

void loop() {
  // put your main code here, to run repeatedly:

  int lectura1 = lecturaSensor(SHARP_1);
  int lectura2 = lecturaSensor(SHARP_2);
  int lectura3 = lecturaSensor(SHARP_3);

  if (lectura1 > 15) {
    runBackwards();
  } else {
    runForward();
  }

}
