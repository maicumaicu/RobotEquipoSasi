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
#define ADELANTE 0
#define ATRAS 1

#define SHARP_1 26  
#define SHARP_2 25
#define SHARP_3 33  

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

void setup() {
  Serial.begin(115200);
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
      robotState = MAPPING;
     /*if (flagButtonMapping == 1) {
        robotState = MAPPING;
      }

      if(flagButtonRunning1 == 1){
        robotState = RUNNING;
      }

      if(flagButtonRunning2 == 1){
        robotState = MAPPING;
      }*/

      break;
    case MAPPING:
      if (digitalRead(15) == HIGH) {
          Map[actual.x][actual.y].final = false;
          ChooseNextNode(actual.x, actual.y);
      } 
      if(digitalRead(5) == HIGH){
        resetAxis();
        actual.x = ALTO;
        actual.y = ANCHO;
        robotState = RESOLUTION;
      }
      break;

    case RESOLUTION:
      addDirection(actual.x, actual.y);
      break;
  }
}
