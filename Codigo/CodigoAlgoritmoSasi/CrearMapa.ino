

void createVisualNode(int x, int y, int adelante, int izquierda, int derecha, int atras, bool final) {
  VisualMap[x][y].visitado = 0;
  VisualMap[x][y].Lados[ADELANTE] = adelante;
  VisualMap[x][y].Lados[IZQUIERDA] = izquierda;
  VisualMap[x][y].Lados[DERECHA] = derecha;
  VisualMap[x][y].Lados[ATRAS] = atras;
  VisualMap[x][y].final = final;
}

void createVisualMap() {
  createVisualNode(0, 0, 0, 1, 1, 1, 0);
  createVisualNode(0, 1, 0, 1, 0, 0, 0);
  createVisualNode(0, 2, 0, 1, 1, 0, 0);
  createVisualNode(0, 3, 1, 1, 0, 0, 0);

  createVisualNode(1, 0, 1, 1, 0, 1, 1);
  createVisualNode(1, 1, 1, 0, 0, 1, 0);
  createVisualNode(1, 2, 0, 1, 0, 1, 0);
  createVisualNode(1, 3, 1, 0, 0, 0, 0);

  createVisualNode(2, 0, 1, 0, 0, 1, 0);
  createVisualNode(2, 1, 1, 0, 0, 1, 0);
  createVisualNode(2, 2, 1, 0, 0, 1, 0);
  createVisualNode(2, 3, 1, 0, 0, 1, 0);

  createVisualNode(3, 0, 0, 0, 1, 1, 0);
  createVisualNode(3, 1, 1, 0, 1, 0, 0);
  createVisualNode(3, 2, 1, 0, 1, 1, 0);
  createVisualNode(3, 3, 1, 0, 1, 1, 0);
}

void PrintVisualMap() {
  for (int i = 0; i < alto; i++) {
    for (int j = 0; j < ancho; j++) {
      SerialBT.print(VisualMap[i][j].visitado);
    }
    SerialBT.println();
  }
}
