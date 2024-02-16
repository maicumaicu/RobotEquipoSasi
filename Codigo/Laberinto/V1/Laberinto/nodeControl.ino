void moveNode(int lado, Position *a) {
  switch (lado) {
  case ADELANTE:
    //if (visual.y != ALTO - 1) {
    a->y++;
    //visual.y++;
    //}
    break;
  case IZQUIERDA:
    //if (visual.x != 0) {
    a->x--;
    //visual.x--;
    //}
    break;
  case DERECHA:
    // if (visual.x != ANCHO - 1) {
    a->x++;
    // visual.x++;
    // }
    break;
  case ATRAS:
    // if (visual.y != 0) {
    a->y--;
    // visual.y--;
    // }

    break;
  }
}

void CreateNode(Node* m, int Sensors[4], int direcciones[4], float maxDistance[3]) {
  m->Lados[direcciones[ADELANTE]] = lecturaSensor(ADELANTE, Sensors, maxDistance);
  m->Lados[direcciones[IZQUIERDA]] = lecturaSensor(IZQUIERDA, Sensors,  maxDistance);
  m->Lados[direcciones[DERECHA]] = lecturaSensor(DERECHA, Sensors, maxDistance);
  m->Lados[direcciones[ATRAS]] = lecturaSensor(ATRAS, Sensors,  maxDistance);
}

void EliminateNode(Node *m, Node* l, int d) {
//Serial.println("Borro");
  m->Lados[d] = 1;
  l->visitado = 0;
}
