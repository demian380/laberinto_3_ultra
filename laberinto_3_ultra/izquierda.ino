void girar_izquierda(){

  while(frente < 12){ //Ver si funciona esto, caso contrario girar por 900 ms (depende de la superficie)

    analogWrite(vel_motor_izq, 0); //se bloquea para inicializar las entradas con pulso 0 o apagado
    analogWrite(vel_motor_izq, 0);
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);

    analogWrite(vel_motor_izq, 160);
    analogWrite(vel_motor_der, 135);

    //Giro sobre su eje hacia la izquierda
    digitalWrite(i1, LOW); //Gira izquierda hacia atrás
    digitalWrite(i2, HIGH);
    digitalWrite(d1, HIGH); //Gira derecha hacia adelante
    digitalWrite(d2, LOW);
    
    digitalWrite(trigger_frente, LOW); 
    delayMicroseconds(2);              
    digitalWrite(trigger_frente, HIGH); 
    delayMicroseconds(5);
    digitalWrite(trigger_frente, LOW);
    duracion_frente = pulseIn(echo_frente, HIGH); 
    frente = duracion_frente/29/2;
    
    digitalWrite(trigger_izq, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_izq, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger_izq, LOW);
    duracion_izq = pulseIn(echo_izq, HIGH);
    izquierda = duracion_izq/29/2; 

  /*
    analogWrite(vel_motor_izq, 160);
    analogWrite(vel_motor_der, 135);

    //Giro sobre su eje hacia la izquierda
    digitalWrite(i1, LOW); //Gira izquierda hacia atrás
    digitalWrite(i2, HIGH);
    digitalWrite(d1, HIGH); //Gira derecha hacia adelante
    digitalWrite(d2, LOW);

    delay(giro); */

    if(frente < 2 || frente > 900 || izquierda < 2 || izquierda > 1000){

      retroceder();
      
    }
  } //cierre while frente menor a 12

  digitalWrite(trigger_der, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_der, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_der, LOW);
  duracion_der = pulseIn(echo_der, HIGH);
  derecha = duracion_der/29/2;

  digitalWrite(trigger_frente, LOW); 
  delayMicroseconds(2);              
  digitalWrite(trigger_frente, HIGH); 
  delayMicroseconds(5);
  digitalWrite(trigger_frente, LOW);
  duracion_frente = pulseIn(echo_frente, HIGH); 
  frente = duracion_frente/29/2;

  while (derecha < 8 && frente > 9){ //refuerzo para que termine de girar

    analogWrite(vel_motor_izq, 0); //se bloquea para inicializar las entradas con pulso 0 o apagado
    analogWrite(vel_motor_izq, 0);
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    
    analogWrite(vel_motor_izq, 85);
    analogWrite(vel_motor_der, 135);
    
    adelante();

    digitalWrite(trigger_der, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_der, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger_der, LOW);
    duracion_der = pulseIn(echo_der, HIGH);
    derecha = duracion_der/29/2;

    digitalWrite(trigger_frente, LOW); 
    delayMicroseconds(2);              
    digitalWrite(trigger_frente, HIGH); 
    delayMicroseconds(5);
    digitalWrite(trigger_frente, LOW);
    duracion_frente = pulseIn(echo_frente, HIGH); 
    frente = duracion_frente/29/2;
    
  }
}
