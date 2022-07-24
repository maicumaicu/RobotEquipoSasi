int a;

void addDirection(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
    SerialBT.println("Adelante1");
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE]);
    directions.concat("a");
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]] != 1) {
    SerialBT.println("IZQUIERDA1");
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA]);
    rotateAxis(IZQUIERDA);
    directions.concat("i");
  } else if (Map[x][y].Lados[direcciones[DERECHA]] != 1) {
    SerialBT.println("DERECHA1");
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA]);
    rotateAxis(DERECHA);
    directions.concat("d");
  }
  directionsSize++;
}

String optimizeDirections(String moves) {
  String finalMoves;
  for (int g = 0; g > directionsSize) {
    if (moves[g] == 'a') {
      a++;
    } else {
      if (a > 1) {
        finalMoves.concat(a);
      }
      a = 0;
      finalMoves.concat(moves[g]);
    }
  }
  return finalMoves;
}


void runDirections(String moves) {
  movementMachine(moves[m]);
}
