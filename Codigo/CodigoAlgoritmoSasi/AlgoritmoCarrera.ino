void addDirection(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
    Serial.println("Adelante1");
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE]);
    directions.concat("a");
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
    Serial.println("IZQUIERDA1");
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA]);
    rotateAxis(IZQUIERDA);
    directions.concat("i");
  } else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
    Serial.println("DERECHA1");
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA]);
    rotateAxis(DERECHA);
    directions.concat("d");
  } else if (Map[x][y].Lados[direcciones[ATRAS]] != 1) {
    Serial.println("atras1");
    rotateAxis(DERECHA);
    rotateAxis(DERECHA);
  }
}
