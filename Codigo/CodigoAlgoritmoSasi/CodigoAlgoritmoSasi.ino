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
int finalX = 4;
int finalY = 2;
Position actual;
Position visual;
Node Map[alto][ancho];
Node VisualMap[ALTO][ANCHO];


void setup() {
  visual.x = 4;
  visual.y = 0;
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
  if (VisualMap[visual.x][visual.y].final == false) {
    Map[actual.x][actual.y].final = false
    ChooseNextNode(actual.x, actual.y);
    PrintMap();
    Serial.println();
  } else if ( c == 0) {
    Map[actual.x][actual.y].final = true
    c++;
    PrintMap();
  }
  // put your mai n code here, to run repeatedly:

}
