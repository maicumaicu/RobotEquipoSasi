#include <Preferences.h>
#include <analogWrite.h>
#include <BluetoothSerial.h>
#include "Wire.h"
#include <MPU6050_light.h>

#define AIN1 19
#define AIN2 18
#define PWMA 27
#define BIN2 17
#define BIN1 32
#define PWMB 12
#define STBY 15

#define MOTOR_A 0
#define MOTOR_B 1

#define SHARP_D 26
#define SHARP_C 25
#define SHARP_I 33

#define CNY70 13

#define encoderPinA1 23
#define encoderPinB1 1

#define encoderPinA2 16
#define encoderPinB2 35

#define DIAMETRO_RUEDA 42.2


#define ALTO 4
#define ANCHO 4

#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3
#define OFF 4

#define PARED 1
#define LIBRE 0

#define SETUP 0
#define MAPPING 1
#define RESOLUTION 2
#define RACING 3

#define NEGRO 1

struct Node {
  public:
    int Lados[4];
    int visitado;
    bool final;
};

struct Position {
  public:
    int x;
    int y;
};


MPU6050 mpu(Wire);
unsigned long timer = 0;


int c,m,directionsSize;
int direcciones[4];
const int alto = ALTO * 2;
const int ancho = ANCHO * 2;
int robotState = SETUP;
int movementState = OFF;
String directions;
Position actual;

Position last;
Node Map[alto][ancho];

//visual map creation
Position visual;
Node VisualMap[ALTO][ANCHO];

volatile int counterD = 0;
volatile int counterI = 0;
volatile boolean flag;
int offset = 0;

int powerA = 20;
int powerB = 20;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Preferences preferences;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("MISA");
  initializeMPU6050();
  initializeSharp();
  initializeMotors ();
  initializeEncoders();

  createVisualMap();
  //preferences.begin("run", false);
  //preferences.clear();
  robotState = 0;
}

void loop() {
  if ((millis() - timer) > 5) {
    runOff(0, 0);
    digitalWrite(STBY, LOW);
    mpu.update();
    timer = millis();
  }
   digitalWrite(STBY, HIGH);
  robotMachine();
}

void robotMachine() {
  switch (robotState) {
    case SETUP:
      actual.x = ALTO;
      actual.y = ANCHO;
      visual.x = 0;
      visual.y = 0;
      resetAxis();
      PrintMap();
      if (SerialBT.available()) {
        if (SerialBT.read() == '1') {
          robotState = MAPPING;
          SerialBT.println('M');

        }

        if (SerialBT.read() == '2') {
          robotState = RESOLUTION;
          SerialBT.println('R');
        }
      }
      break;
    case MAPPING:
      {
        int valueCNY = lecturaCNY70(20, CNY70);
        /*SerialBT.println(valueCNY);*/
        if (VisualMap[visual.x][visual.y].final == false) {
          Map[actual.x][actual.y].final = false;
          movementMachine(DERECHA/*ChooseNextNode(actual.x, actual.y)*/);
        } else {
          Map[actual.x][actual.y].final = true;
          SerialBT.write('S');
          robotState = RESOLUTION;
        }
      }
      break;

    case RESOLUTION:
      addDirection(actual.x, actual.y);
      break;
    case RACING:
    runDirections("addaad");
      break;
  }
}
