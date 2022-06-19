#define ALTO 5
#define ANCHO 5

#define ADELANTE 0
#define IZQUIERDA 1
#define ATRAS 2
#define DERECHA 3


#define PARED 1
#define LIBRE 0

struct Node {
  public:
    int Lados[4];
    int visitado;
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
int finalX = 4;
int finalY = 9;
Position actual;
Node Map[alto][ancho];


void setup() {
  actual.x = ALTO;
  actual.y = ANCHO;
  for (int i = 0; i < 4; i++) {
    direcciones[i] = i;
  }
  Serial.begin(115200);
  PrintMap();
  Serial.println();
  createVisualMap();
  //ChooseNextNode(actual.x, actual.y);
  Serial.println(Map[actual.x][actual.y - 1].visitado);
  Serial.println(actual.y);
  //PrintMap();
  /* ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    ChooseNextNode(actual.x, actual.y);
    Serial.println(actual.x);
    Serial.println(actual.y);
    PrintMap();*/
}

void loop() {
  if (actual.x != finalX || actual.y != finalY) {
    ChooseNextNode(actual.x, actual.y);
    Serial.println();
  } else if ( c == 0) {
    c++;
    PrintMap();
  }
  // put your mai n code here, to run repeatedly:

}
