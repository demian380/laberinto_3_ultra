void girar_derecha(){

  while(frente < 12){ //Ver si funciona esto, caso contrario girar por 900 ms (depende de la superficie)

    analogWrite(vel_motor_izq, 0); //se bloquea para inicializar las entradas con pulso 0 o apagado
    analogWrite(vel_motor_izq, 0);
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    
    analogWrite(vel_motor_izq, 160); 
    analogWrite(vel_motor_der, 135);

    //Giro sobre su eje hacia la derecha
    digitalWrite(i1, HIGH); //Gira izquierda hacia adelante
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW); //Gira derecha hacia atrás
    digitalWrite(d2, HIGH);

    digitalWrite(trigger_frente, LOW); 
    delayMicroseconds(2);              
    digitalWrite(trigger_frente, HIGH); 
    delayMicroseconds(5);
    digitalWrite(trigger_frente, LOW);
    duracion_frente = pulseIn(echo_frente, HIGH); 
    frente = duracion_frente/29/2;

    digitalWrite(trigger_der, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_der, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger_der, LOW);
    duracion_der = pulseIn(echo_der, HIGH);
    derecha = duracion_der/29/2; 

    /*
    analogWrite(vel_motor_izq, 160); 
    analogWrite(vel_motor_der, 135);

    //Giro sobre su eje hacia la derecha
    digitalWrite(i1, HIGH); //Gira izquierda hacia adelante
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW); //Gira derecha hacia atrás
    digitalWrite(d2, HIGH);

    delay(giro); */

    if(frente < 2 || frente > 900 || derecha < 2 || derecha > 900){
      
      retroceder();
      
    }
  } //cierre while frente menor a 12

  detener();

  digitalWrite(trigger_izq, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_izq, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_izq, LOW);
  duracion_izq = pulseIn(echo_izq, HIGH);
  izquierda = duracion_izq/29/2;

  //referencia_izq = izquierda - 2;  //PROBAR ESTO EN CASO QUE NO TERMINE DE GIRAR CON EL "WHILE < 12"

  digitalWrite(trigger_frente, LOW); 
  delayMicroseconds(2);              
  digitalWrite(trigger_frente, HIGH); 
  delayMicroseconds(5);
  digitalWrite(trigger_frente, LOW);
  duracion_frente = pulseIn(echo_frente, HIGH); 
  frente = duracion_frente/29/2;
  
  while (izquierda < 8 && frente > 9){ //refuerzo para que termine de girar (si hace falta, aumentar el valor de distancia a la pared izquierda)

    analogWrite(vel_motor_izq, 0); //se bloquea para inicializar las entradas con pulso 0 o apagado
    analogWrite(vel_motor_izq, 0);
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);

    analogWrite(vel_motor_izq, 160);
    analogWrite(vel_motor_der, 85);
    
    adelante();

    digitalWrite(trigger_izq, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_izq, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger_izq, LOW);
    duracion_izq = pulseIn(echo_izq, HIGH);
    izquierda = duracion_izq/29/2;

    digitalWrite(trigger_frente, LOW); 
    delayMicroseconds(2);              
    digitalWrite(trigger_frente, HIGH); 
    delayMicroseconds(5);
    digitalWrite(trigger_frente, LOW);
    duracion_frente = pulseIn(echo_frente, HIGH); 
    frente = duracion_frente/29/2;
    
  }
}
