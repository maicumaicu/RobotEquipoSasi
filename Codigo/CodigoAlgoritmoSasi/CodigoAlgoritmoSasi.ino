#include <Preferences.h>
#include <analogWrite.h>
#include <BluetoothSerial.h>
#include "Wire.h"
#include <MPU6050_light.h>

#define AIN1 19
#define AIN2 18
#define PWMA 14
#define BIN2 17
#define BIN1 32
#define PWMB 12

#define MOTOR_A 0
#define MOTOR_B 1

#define LED_1 2
#define LED_2 4

#define SHARP_D 26
#define SHARP_C 25
#define SHARP_I 33

#define CNY70 13

#define encoderPinA1 23
#define encoderPinB1 27

#define encoderPinA2 34
#define encoderPinB2 35

#define DIAMETRO_RUEDA 42.2


#define ALTO 5
#define ANCHO 5

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


int c, move;
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
int finalX = 4;
int finalY = 4;
Position visual;
Node VisualMap[ALTO][ANCHO];

volatile int counterD = 0;
volatile int counterI = 0;
volatile boolean flag;
int offset = 0;

int powerA = 40;
int powerB = 50;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Preferences preferences;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("MISA");
  initializeMPU6050();
  //initializeLeds();
  initializeSharp();
  initializeMotors ();
  initializeEncoders();
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  createVisualMap();
  //preferences.begin("run", false);
  //preferences.clear();
  robotState = 0;
}

void loop() {
  if ((millis() - timer) > 5) {
    runOff(0, 0);
    mpu.update();
    timer = millis();
  }
  robotMachine();
}

void robotMachine() {
  switch (robotState) {
    case SETUP:
      actual.x = ALTO;
      actual.y = ANCHO;
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
        /*int valueCNY = lecturaCNY70(20, CNY70);
          SerialBT.println(valueCNY);*/
        //SerialBT.println(counterD);
        if (VisualMap[visual.x][visual.y].final == false) {
          Map[actual.x][actual.y].final = false;
          movementMachine();
        } else {
          Map[actual.x][actual.y].final = true;
          SerialBT.write('S');
          robotState = SETUP;
        }
      }
      break;

    case RESOLUTION:
      addDirection(actual.x, actual.y);
      break;
  }
}
