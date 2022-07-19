#include <analogWrite.h>
// Define model and input pin:
#define model 430

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



//unsigned long timer = 0;
int lectura = 0;

hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer() {
  lectura = lecturaSensor(20, SHARP_1);
  Serial.println(lectura);
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);

  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);

  /* Set alarm to call onTimer function every second 1 tick is 1us
    => 1 second is 1000000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 1000000, true);

  /* Start an alarm */
  timerAlarmEnable(timer);

  //pinMode(2, OUTPUT);
  // pinMode(4, OUTPUT);
  initializeSharp();
  initializeMotors();

}

void loop() {
  
  /*if ((millis() - timer) > 100 && (millis() - timer) < 120) {
    digitalWrite(15, LOW);
    runOff();
    delay(1000);
    lectura = lecturaSensor(20, SHARP_1);
    timer = millis();
    } else {
    Serial.println(lectura);
    digitalWrite(15, HIGH);
    //runForward();
    }*/
}
