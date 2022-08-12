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
#define PWMB 14
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


#define ALTO 5
#define ANCHO 5

#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3
#define SUPER 4
#define OFF 5

#define READING 0
#define CHOOSING 1
#define MOVING 2

#define SETUP 0
#define MAPPING 1
#define RESOLUTION 2
#define RACING 3

#define NEGRO 1
#define BLANCO 0

#define PARED 1
#define LIBRE 0

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


int c, m, directionsSize, movimiento;
int finishFlag, movimientoFlag;
int valueCNY;
int direcciones[4];
const int alto = ALTO * 2;
const int ancho = ANCHO * 2;
int mainState = SETUP;
int robotState = READING;
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
int estabilizationOffset = 0;

int powerA = 100;
int powerB = 100;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
Preferences preferences;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("MISA");
  preferences.begin("run", false);
  pinMode(2, OUTPUT);
  pinMode(CNY70, INPUT);
  initializeMPU6050();
  initializeSharp();
  initializeMotors ();
  initializeEncoders();
  createVisualMap();
  mainState = 0;

}

void loop() {
  if ((millis() - timer) > 5) {
    runOff(0, 0);
    digitalWrite(STBY, LOW);
    mpu.update();
    timer = millis();
  }
  SerialBT.println(lecturaCNY70(20, CNY70));
  //delay(1000);
  digitalWrite(STBY, HIGH);
  mainMachine();
}

void mainMachine() {
  switch (mainState) {
    case SETUP:
      actual.x = ALTO;
      actual.y = ANCHO;
      visual.x = 0;
      visual.y = 0;
      resetAxis();
      movimientoFlag = 0;
      finishFlag = 0;
      //PrintMap();
      /*if (digitalRead(4) == LOW) {
        mainState = RACING;
        noInterrupts();
        directions = ReadRun();
        interrupts();
        //ShowRun();
        SerialBT.println('R');
        }
        if (digitalRead(4) == LOW) {
        mainState = MAPPING;
        interrupts();
        SerialBT.println('M');
        estabilizationOffset = getTurnAngle();
        }*/
      if (SerialBT.available()) {
        char read = SerialBT.read();
        if (read == '1') {
          mainState = MAPPING;
          interrupts();
          SerialBT.println('M');
          estabilizationOffset = getTurnAngle();
        }
        if (read == '2') {
          mainState = RACING;
          noInterrupts();
          directions = ReadRun();
          interrupts();
          //ShowRun();
          SerialBT.println('R');
        }
      }
      confirmacionCentrado();
      break;
    case MAPPING:
      {
        if (finishFlag == 0) {
          robotMachine();
        } else {
          actual.x = ALTO;
          actual.y = ANCHO;
          visual.x = 0;
          visual.y = 0;
          finishFlag = 0;
          resetAxis();
          PrintMap();
          noInterrupts();
          mainState = RESOLUTION;
        }
      }
      break;
    case RESOLUTION:
      if (Map[actual.x][actual.y].final == false) {
        addDirection(actual.x, actual.y);
      } else {
        SerialBT.println(directions);
        directions = optimizeDirections(directions);
        SerialBT.println(directions);
        UploadRun(directions);
        mainState = SETUP;
      }

      break;
    case RACING:
      runDirections(directions);
      break;
  }
}


void robotMachine() {
  switch (robotState) {
    case READING:
      //SerialBT.println("Rea");
      //
      Map[actual.x][actual.y].visitado++;
      if (Map[actual.x][actual.y].visitado == 1) {
        Serial.println("creo nodo");
        runOff(0, 0);
        CreateNode(actual.x, actual.y);
      }
      valueCNY = lecturaCNY70(20, CNY70);

      /*if (valueCNY == BLANCO) {
              Map[actual.x][actual.y].final = true;
              finishFlag = 1;
            } else {
              Map[actual.x][actual.y].final = false;
              robotState = CHOOSING;
            }*/
      Map[actual.x][actual.y].final = false;
      robotState = CHOOSING;
      //delay(1000);
      break;
    case CHOOSING:
      //SerialBT.println("Cho");
      movimiento = ChooseNextNode(actual.x, actual.y);
      movimientoFlag = 0;
      robotState = MOVING;
      break;
    case MOVING:
      movementMachine(movimiento);
      if (movimientoFlag == 1) {
        robotState = READING;
      }
      //SerialBT.println("Mov");
      break;
  }
}
