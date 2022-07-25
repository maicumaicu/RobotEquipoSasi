int a;

void addDirection(int x, int y) {
  if (Map[x][y].Lados[direcciones[ADELANTE]] != 1) {
    SerialBT.println("Adelante1");
    Map[x][y].Lados[direcciones[ADELANTE]] = 2;
    moveNode(direcciones[ADELANTE]);
    directions.concat("a");
  } else if (Map[x][y].Lados[direcciones[IZQUIERDA]]  != 1) {
    SerialBT.println("IZQUIERDA1");
    Map[x][y].Lados[direcciones[IZQUIERDA]] = 2;
    moveNode(direcciones[IZQUIERDA]);
    rotateAxis(IZQUIERDA);
    directions.concat("i");
  } else if (Map[x][y].Lados[direcciones[DERECHA]]  != 1) {
    SerialBT.println("DERECHA1");
    Map[x][y].Lados[direcciones[DERECHA]] = 2;
    moveNode(direcciones[DERECHA]);
    rotateAxis(DERECHA);
    directions.concat("d");
  }
  directionsSize++;
}

String optimizeDirections(String moves) {
  String finalMoves = "";
  for (int g = 0; g < directionsSize; g++) {
    if (moves[g] == 'a') {
      a++;
    } else {
      if (a > 1) {
        finalMoves.concat(a);
      } else  if (a == 1) {
        finalMoves.concat('a');
      }
      a = 0;

      finalMoves.concat(moves[g]);
    }
  }
  if (a == 1) {
    finalMoves.concat('a');
  } else if ( a > 1) {
    finalMoves.concat(a);
  }
  return finalMoves;
}


void runDirections(String moves) {
  if (moves[m] == 'a') {
    movementMachine(ADELANTE);
  } else if (moves[m] == 'd') {
    movementMachine(DERECHA);
  } else if (moves[m] == 'i') {
    movementMachine(IZQUIERDA);
  } else {
    movementMachine(SUPER);
  }
  if (movimientoFlag == 1) {
    m++;
    movimientoFlag = 0;
  }
}
