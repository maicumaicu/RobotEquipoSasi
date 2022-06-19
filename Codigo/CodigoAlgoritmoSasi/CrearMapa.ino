void createVisualNode(int x, int y,int adelante,int izquierda, int derecha,int atras){
  Map[x][y].visitado = 0;
  Map[x][y].Lados[ADELANTE] = adelante;
  Map[x][y].Lados[IZQUIERDA] = izquierda;
  Map[x][y].Lados[DERECHA] = derecha;
  Map[x][y].Lados[ATRAS] = atras;
}

void createVisualMap(){
  createVisualNode(0,0,0,1,1,0);
  createVisualNode(0,1,0,1,1,0);
  createVisualNode(0,2,0,1,1,0);
  createVisualNode(0,3,1,1,0,0);
  createVisualNode(1,3,1,0,0,1);
  createVisualNode(2,3,1,0,0,1);
  createVisualNode(3,3,1,0,0,1);
  createVisualNode(4,3,0,0,0,1);
  createVisualNode(5,3,1,0,0,1);
  createVisualNode(6,3,1,0,0,1);
  createVisualNode(7,3,1,0,0,0);
  createVisualNode(8,3,1,0,0,1);
  createVisualNode(9,3,1,0,1,1);
  createVisualNode(4,4,0,1,1,0);
  createVisualNode(4,5,0,1,1,0);
  createVisualNode(4,6,0,1,1,0);
  createVisualNode(4,7,0,1,1,0);
  createVisualNode(4,8,0,1,1,0);
  createVisualNode(4,9,0,1,1,0);
  createVisualNode(7,2,0,1,1,0);
  createVisualNode(7,1,0,1,1,1);
}

void PrintMap() {
  for (int i = 0; i < alto; i++) {
    for (int j = 0; j < ancho; j++) {
      Serial.print(Map[i][j].visitado);
    }
    Serial.println();
  }
}
