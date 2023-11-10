
float getTurnAngle() {
  sensor.getRotation(&gx, &gy, &gz);

  dt = millis() - tiempo_prev;
  tiempo_prev = millis();

  //Calcular los angulos rotacion:
  girosc_ang_z = (gz / 131) * dt / 1000.0 + girosc_ang_z_prev;
  girosc_ang_z_prev = girosc_ang_z;
  return girosc_ang_z;
}
