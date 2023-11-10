int ChooseNextNode(int x, int y) {
  if (Map[x][y].Lados[direcciones[IZQUIERDA]] == LIBRE) {
    Serial.println("IZQUIERDA");
    moveNode(direcciones[IZQ],&actual);
    rotateAxis(IZQ);
    return IZQ;
    
  } else if (Map[x][y].Lados[direcciones[ADELANTE]] == LIBRE) {
    Serial.println("Adelante");
    moveNode(direcciones[ADE],&actual);
    return ADE;
  } else if (Map[x][y].Lados[direcciones[DERECHA]] == LIBRE) {
    Serial.println("DERECHA");
    moveNode(direcciones[DER],&actual);
    rotateAxis(DER);
    return DER;
  } else {
    Serial.println("otro");
     moveNode(direcciones[ATR],&actual);
    return ATR;
  }
  last.x = x;
  last.y = y;
}
