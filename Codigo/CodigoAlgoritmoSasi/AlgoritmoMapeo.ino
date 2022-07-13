void ChooseNextNode(int x, int y) {
  Map[x][y].visitado++;
  if (Map[x][y].visitado == 1) {
    Serial.println("creo nodo");
    CreateNode(x, y);
  }
  if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
    runForward();
    Serial.println("Adelante");
    SerialBT.write('A');
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE]);
    if (Map[x][y].Lados[direcciones[ATRAS]] != 1) Map[x][y].Lados[direcciones[ATRAS]] = 2;
    if (Map[x][y].visitado > 1 ) {
      EliminateNode(x, y);
    }
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
    runLeft();
    Serial.println("IZQUIERDA");
     SerialBT.write('I');
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA]);
    if (Map[x][y].Lados[direcciones[ATRAS]] != 1) Map[x][y].Lados[direcciones[ATRAS]] = 2;
    rotateAxis(IZQUIERDA);
    if (Map[x][y].visitado > 1 ) {
      EliminateNode(x, y);
    }
  } else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
    runRight();
    Serial.println("DERECHA");
     SerialBT.write('D');
    ledOff(LED_1);
    ledOff(LED_2);
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA]);
    if (Map[x][y].Lados[direcciones[ATRAS]] != 1) Map[x][y].Lados[direcciones[ATRAS]] = 2;
    rotateAxis(DERECHA);
    if (Map[x][y].visitado > 1 ) {
      EliminateNode(x, y);
    }
  } else {
    ledOff(LED_1);
    ledOff(LED_2);
    Serial.println("otro");
     SerialBT.write('O');
    SearchAvailableNode(x, y);
  }

  last.x = x;
  last.y = y;


  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.println(" ");
  Serial.print(visual.x);
  Serial.print(" ");
  Serial.print(visual.y);
  Serial.println(" ");
  Serial.print(Map[x][y].Lados[direcciones[ADELANTE]]);
  Serial.print(" ");
  Serial.print(Map[x][y].Lados[direcciones[DERECHA]]);
  Serial.print(" ");
  Serial.print(Map[x][y].Lados[direcciones[IZQUIERDA]]);
  Serial.print(" ");
  Serial.println(Map[x][y].Lados[direcciones[ATRAS]]);
  Serial.print(direcciones[ADELANTE]);
  Serial.print(" ");
  Serial.print(direcciones[DERECHA]);
  Serial.print(" ");
  Serial.print(direcciones[IZQUIERDA]);
  Serial.print(" ");
  Serial.println(direcciones[ATRAS]);
}

void EliminateNode(int x, int y) {
  Serial.println("Borro");
  Map[x][y].Lados[direcciones[ATRAS]] = 1;
  Map[last.x][last.y].visitado = 0;
}

void SearchAvailableNode(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
    Serial.println("Adelante1");
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE]);
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
    Serial.println("IZQUIERDA1");
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA]);
    rotateAxis(IZQUIERDA);
  } else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
    Serial.println("DERECHA1");
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA]);
    rotateAxis(DERECHA);
  } else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
    Serial.println("atras1");
    rotateAxis(DERECHA);
    rotateAxis(DERECHA);
  }
}
void moveNode(int lado) {
  switch (lado) {
    case ADELANTE:
      if (visual.y != ALTO - 1) {
        actual.y++;
        visual.y++;
      }
      break;
    case IZQUIERDA:
      if (visual.x != 0) {
        actual.x--;
        visual.x--;
      }
      break;
    case DERECHA:
      if (visual.x != ANCHO - 1) {
        actual.x++;
        visual.x++;
      }
      break;
    case ATRAS:
      if (visual.y != 0) {
        actual.y--;
        visual.y--;
      }

      break;
  }
}

void CreateNode(int x, int y) {
  Map[x][y].Lados[ADELANTE] = lecturaSensor(20, SHARP_C);
  Map[x][y].Lados[IZQUIERDA] = lecturaSensor(20, SHARP_I);
  Map[x][y].Lados[DERECHA] = lecturaSensor(20, SHARP_D);
  Map[x][y].Lados[ATRAS] = 0;
}

void rotateAxis(int direccion) {
  switch (direccion) {
    case DERECHA:
      for (int i = 0; i < 4; i++) {
        direcciones[i] = direcciones[i] - 1;
        if (direcciones[i] == -1) {
          direcciones[i] = 3;
        }
      }
      break;
    case IZQUIERDA:
      for (int j = 0; j < 4; j++) {
        direcciones[j] = direcciones[j] + 1;
        if (direcciones[j] == 4) {
          direcciones[j] = 0;
        }
      }
      break;
  }
}





void resetAxis() {
  for (int i = 0; i < 4; i++) {
    direcciones[i] = i;
  }
}

/*int cantVueltas(){

  }*/

void PrintMap() {
  for (int i = 0; i < alto; i++) {
    for (int j = 0; j < ancho; j++) {
      Serial.print(Map[i][j].visitado);
      Serial.print(" ");
    }
    Serial.println();
  }
}
