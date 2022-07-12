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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  initializeSharp();
  initializeMotors();

}

void loop() {
  // put your main code here, to run repeatedly:

  int lectura1 = lecturaSensor(20,SHARP_1);
  int lectura2 = lecturaSensor(20,SHARP_2);
  int lectura3 = lecturaSensor(20,SHARP_3);
  Serial.println(lectura1);
  if (lectura2 > 7) {
     runBackwards();
  } else {
    runForward();
  }
  delay(1000);
}
