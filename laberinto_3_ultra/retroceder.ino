void retroceder(){
      
    analogWrite(vel_motor_izq, 160);
    analogWrite(vel_motor_der, 135);

    digitalWrite(i1, LOW);
    digitalWrite(i2, HIGH);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);

    delay(retraso);
      
}
