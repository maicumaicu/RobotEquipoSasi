void ChooseNextNode(int x, int y) {
  Map[x][y].visitado++;
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.print(direcciones[ADELANTE]);
  Serial.print(" ");
  Serial.print(direcciones[IZQUIERDA]);
  Serial.print(" ");
  Serial.print(direcciones[DERECHA]);
  Serial.print(" ");
  Serial.println(direcciones[ATRAS]);
  if (Map[x][y].Lados[direcciones[ADELANTE]] == 0) {
    Serial.println("Adelante");
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE]);
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] == 0) {
    Serial.println("IZQUIERDA");
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA]);
    rotateAxis(IZQUIERDA);
  } else if (Map[x][y].Lados[direcciones[DERECHA]] == 0) {
    Serial.println("DERECHA");
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA]);
    rotateAxis(DERECHA);
  } else {
    Serial.println("otro");
    SearchAvailableNode(x,y);
  }
  Map[actual.x][actual.y].Lados[direcciones[ATRAS]] = 2;
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
      if (actual.y != alto - 1) {
        actual.y++;
      }
      break;
    case IZQUIERDA:
      if (actual.x != 0) {
        actual.x--;
      }
      break;
    case DERECHA:
      if (actual.x != ancho - 1) {
        actual.x++;
      }
      break;
    case ATRAS:
      if (actual.y != 0) {
        actual.y--;
      }

      break;
  }
}

void CreateNode(int x, int y) {
  Map[x][y].visitado = 0;
  Map[x][y].Lados[ADELANTE] = lecturaSensor(direcciones[ADELANTE]);
  Map[x][y].Lados[IZQUIERDA] = lecturaSensor(direcciones[IZQUIERDA]);
  Map[x][y].Lados[DERECHA] = lecturaSensor(direcciones[DERECHA]);
  Map[x][y].Lados[ATRAS] = lecturaSensor(direcciones[ATRAS]);
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



int lecturaSensor(int direccion) {
  if (direccion == 2) {
    return 1;
  } else {
    return 0;
  }

}
