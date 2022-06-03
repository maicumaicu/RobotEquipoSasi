#define LARGO 10
#define ANCHO 10

#define ADELANTE 0
#define IZQUIERDA 1
#define DERECHA 2
#define ATRAS 3

struct Node {
  public:
    int Lados[4];
    int visitado;
};

int direcciones[4];

Node Map[LARGO][ANCHO];


void setup() {
  Serial.begin(115200);
  PrintMap();
  ChooseNextNode(Map[0][0]);
  for(int i = 0;i<4;i++){
    direcciones[i]=i;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

int ChooseNextNode(Node node){
  if(node.Lados[direcciones[ADELANTE]] == 0){
    return ADELANTE;
  }else if(node.Lados[direcciones[IZQUIERDA]] == 0){
    return IZQUIERDA;
  }else if(node.Lados[direcciones[DERECHA]] == 0){
    return DERECHA;
  }else{
    return ATRAS;
  }
}

void CreateNode(Node node){
  node.visitado = 1;
  node.Lados[direcciones[ADELANTE]] = lecturaSensor(direcciones[ADELANTE]);
  node.Lados[direcciones[IZQUIERDA]] = lecturaSensor(direcciones[IZQUIERDA]);
  node.Lados[direcciones[DERECHA]] = lecturaSensor(direcciones[DERECHA]);
  node.Lados[direcciones[ATRAS]] = 1;
}

int lecturaSensor(int direccion){
  
}


void PrintMap(){
  for(int i =0;i<LARGO;i++){
    for(int j =0;j<ANCHO;j++){
      Serial.print(Map[i][j].visitado);
    }
    Serial.println();
  }
}
