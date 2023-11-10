void moveNode(int lado, Position *a) {
  switch (lado) {
    case ADE:
      //if (visual.y != ALTO - 1) {
      a->y++;
      //visual.y++;
      //}
      break;
    case IZQ:
      //if (visual.x != 0) {
      a->x--;
      //visual.x--;
      //}
      break;
    case DER:
      // if (visual.x != ANCHO - 1) {
      a->x++;
      // visual.x++;
      // }
      break;
    case ATR:
      // if (visual.y != 0) {
      a->y--;
      // visual.y--;
      // }

      break;
  }
}

void CreateNode(Node* m) {
  m->Lados[direcciones[ADE]] = lecturaSharp(1, SC);
  m->Lados[direcciones[IZQ]] = lecturaSharp(1, SI);
  m->Lados[direcciones[DER]] = lecturaSharp(1, SD);
  m->Lados[direcciones[ATR]] = 0;
}

void EliminateNode(Node *m, Node* l, int d) {
  //Serial.println("Borro");
  m->Lados[d] = 1;
  l->visitado = 0;
}
