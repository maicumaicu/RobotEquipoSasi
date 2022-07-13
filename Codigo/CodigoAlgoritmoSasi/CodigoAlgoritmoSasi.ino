#include <Preferences.h>
#include <analogWrite.h>


#define AIN1 18
#define AIN2 19
#define PWMA 14
#define BIN2 32
#define BIN1 17
#define PWMB 12
#define MOTOR_A 0
#define MOTOR_B 1

#define LED_1 2
#define LED_2 4

#define SHARP_D 26
#define SHARP_C 25
#define SHARP_I 33

#define CNY70 13

#define ALTO 5
#define ANCHO 5

#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3

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

int c;
int direcciones[4];
const int alto = ALTO * 2;
const int ancho = ANCHO * 2;
int robotState;
String directions;
Position actual;

Position last;
Node Map[alto][ancho];

//visual map creation
int finalX = 4;
int finalY = 4;
Position visual;
Node VisualMap[ALTO][ANCHO];

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("MISA");
  initializeLeds();
  initializeSharp();
  //preferences.begin("run", false);
  //preferences.clear();
  robotState = 0;
}

void loop() {
  robotMachine();
  /*if (VisualMap[visual.x][visual.y].final == false) {

    PrintMap();
    Serial.println();
    } else if ( c == 0) {
    Map[actual.x][actual.y].final = true;
    c++;
    PrintMap();
    visual.x = 4;
    visual.y = 4;
    actual.x = ALTO;
    actual.y = ANCHO;
    } else if (Map[actual.x][actual.y].final == true) {
    addDirection(actual.x, actual.y);
    Serial.println(directions);
    }*/
}

void robotMachine() {
  switch (robotState) {
    case SETUP:
      actual.x = ALTO;
      actual.y = ANCHO;
      resetAxis();
      PrintMap();
      //robotState = MAPPING;
      if (SerialBT.available()) {
        if (SerialBT.read() == '1') {
          robotState = MAPPING;
          SerialBT.write('M');
        }

        if (SerialBT.read() == '2') {
          robotState = RESOLUTION;
          SerialBT.write('R');
        }
      }

      break;
    case MAPPING:
      {
        int valueCNY = analogRead(CNY70);
        //SerialBT.write(valueCNY);
        Serial.println(valueCNY);
        if (valueCNY > 800) {
          Map[actual.x][actual.y].final = false;
          ChooseNextNode(actual.x, actual.y);
        } else {
          resetAxis();
          actual.x = ALTO;
          actual.y = ANCHO;
          SerialBT.write('R');
          robotState = RESOLUTION;
        }
      }
      break;

    case RESOLUTION:
      addDirection(actual.x, actual.y);
      break;
  }
}
