void detener(){
  analogWrite(vel_motor_izq, 0);
  analogWrite(vel_motor_izq, 0);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);

  delay(retraso);
}
