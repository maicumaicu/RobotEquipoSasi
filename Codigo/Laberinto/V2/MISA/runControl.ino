void runMachine(int lado) {
  if (lado == IZQUIERDA) {
    if (piso[0] == NEGRO) {
      if (sensores[CENTRO] == PARED) {
        if (sensores[IZQUIERDA] == LIBRE) {
          //izquierda 90
          showModeNumber(0);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ);
          showModeNumber(0);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        } else if (sensores[DERECHA] == LIBRE) {
          showModeNumber(1);
          runMotor(ADELANTE, &Motors[MOT_IZQ]);
          runMotor(ATRAS, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_DER);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        } else {
          //izquierda 180
          showModeNumber(2);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ * 2);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        }
      } else {
        /*if(sensores[IZQUIERDA] == PARED){
          //izquierda 90
          }*/

        //showModeNumber(3);
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        angularPID(IZQUIERDA, pd[0]);

      }
    } else {
      showModeNumber(3);
      runMotor(ATRAS, &Motors[MOT_IZQ]);
      runMotor(ADELANTE, &Motors[MOT_DER]);
      analogWrite(9, 100);
      analogWrite(11, 100);
      delay(500);
      runMotor(OFF, &Motors[MOT_IZQ]);
      runMotor(OFF, &Motors[MOT_DER]);
      analogWrite(9, 0);
      analogWrite(11, 0);
      delay(2000);
    }
  } else {
    if (piso[0] == NEGRO) {
      if (sensores[CENTRO] == PARED) {
        if (sensores[DERECHA] == LIBRE) {
          showModeNumber(1);
          runMotor(ADELANTE, &Motors[MOT_IZQ]);
          runMotor(ATRAS, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_DER);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        }
        else if (sensores[IZQUIERDA] == LIBRE) {
          //izquierda 90
          showModeNumber(0);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ);
          showModeNumber(0);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        } else {
          //izquierda 180
          showModeNumber(2);
          runMotor(ATRAS, &Motors[MOT_IZQ]);
          runMotor(ADELANTE, &Motors[MOT_DER]);
          analogWrite(9, 100);
          analogWrite(11, 100);
          delay(GIRO_IZQ * 2);
          runMotor(OFF, &Motors[MOT_IZQ]);
          runMotor(OFF, &Motors[MOT_DER]);
          analogWrite(9, 0);
          analogWrite(11, 0);
        }
      } else {
        /*if(sensores[IZQUIERDA] == PARED){
          //izquierda 90
          }*/

        //showModeNumber(3);
        runMotor(ADELANTE, &Motors[MOT_IZQ]);
        runMotor(ADELANTE, &Motors[MOT_DER]);
        angularPID(DERECHA, pd[0]);

      }
    } else {
      showModeNumber(3);
      runMotor(ATRAS, &Motors[MOT_IZQ]);
      runMotor(ADELANTE, &Motors[MOT_DER]);
      analogWrite(9, 100);
      analogWrite(11, 100);
      delay(500);
      runMotor(OFF, &Motors[MOT_IZQ]);
      runMotor(OFF, &Motors[MOT_DER]);
      analogWrite(9, 0);
      analogWrite(11, 0);
      delay(2000);
    }
  }
}
