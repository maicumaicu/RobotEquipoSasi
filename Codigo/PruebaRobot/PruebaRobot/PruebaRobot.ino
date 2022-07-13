#include <analogWrite.h>

#define AIN1 19
#define AIN2 18
#define PWMA 14
#define BIN2 17
#define BIN1 32
#define PWMB 12
#define MOTOR_A 0
#define MOTOR_B 1
#define ADELANTE 0
#define ATRAS 1
#define OFF 2

#define SHARP_1 26
#define SHARP_2 25
#define SHARP_3 33


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  initializeSharp();
  initializeMotors();

}

void loop() {
    runForward();
}
