void secuencia_inicial(){

  digitalWrite(trigger_izq, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_izq, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_izq, LOW);
  duracion_izq = pulseIn(echo_izq, HIGH);
  izquierda = duracion_izq/29/2;

  digitalWrite(trigger_der, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_der, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_der, LOW);
  duracion_der = pulseIn(echo_der, HIGH);
  derecha = duracion_der/29/2;

  digitalWrite(trigger_frente, LOW); //se declaran las respectivas entradas y salidas de señales del ultrasónico y almacenada por la variable del sensor
  delayMicroseconds(2);              // que convierte la velocidad del sonido que es de 340 m/s por 29 microsengundos por cm, como la señal va y viene 
  digitalWrite(trigger_frente, HIGH); //ese tiempo es la mitad  siendo sensor = tiempo/29/2
  delayMicroseconds(5);
  digitalWrite(trigger_frente, LOW);
  duracion_frente = pulseIn(echo_frente, HIGH); //Estos calculos siguen con los otros sensores
  frente = duracion_frente/29/2;

  if(izquierda > 9 && derecha > 9){ //Si no hay paredes al comienzo que avance la distancia de 900 ms (un autito de distancia aprox)

    analogWrite(vel_motor_izq, 0); //se bloquea para inicializar las entradas con pulso 0 o apagado
    analogWrite(vel_motor_izq, 0);
    digitalWrite(i1, LOW);
    digitalWrite(i2, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);

    /* ------- QUE AVANCE 1000 Ms AL COMIENZO ------- */
    analogWrite(vel_motor_izq, 140); 
    analogWrite(vel_motor_der, 155);
  
    adelante();
  
    delay(1000); 
  
    detener();
  
    digitalWrite(trigger_izq, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_izq, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger_izq, LOW);
    duracion_izq = pulseIn(echo_izq, HIGH);
    izquierda = duracion_izq/29/2;
  
    if(izquierda > 10){ //Si a la izquierda no hay nada, gira sobre su eje X Ms hacia la izquierda y se detiene
  
      analogWrite(vel_motor_izq, 140);
      analogWrite(vel_motor_der, 155);
  
      //Giro sobre su eje hacia la izquierda
      digitalWrite(i1, LOW); //Gira izquierda hacia atrás
      digitalWrite(i2, HIGH);
      digitalWrite(d1, HIGH); //Gira derecha hacia adelante
      digitalWrite(d2, LOW);
  
      delay(giro);
  
      //detener();
      
      digitalWrite(trigger_frente, LOW); 
      delayMicroseconds(2);               
      digitalWrite(trigger_frente, HIGH); 
      delayMicroseconds(5);
      digitalWrite(trigger_frente, LOW);
      duracion_frente = pulseIn(echo_frente, HIGH); 
      frente = duracion_frente/29/2;

      while (frente < 14){ //en caso que no haya terminado de girar, verifica si el frente está próximo y gira 350ms más de ser asi

        analogWrite(vel_motor_izq, 140);
        analogWrite(vel_motor_der, 155);
        
        //Giro sobre su eje hacia la izquierda
        digitalWrite(i1, LOW); //Gira izquierda hacia atrás
        digitalWrite(i2, HIGH);
        digitalWrite(d1, HIGH); //Gira derecha hacia adelante
        digitalWrite(d2, LOW);
    
        //delay(retraso);

        digitalWrite(trigger_frente, LOW); 
        delayMicroseconds(2);               
        digitalWrite(trigger_frente, HIGH); 
        delayMicroseconds(5);
        digitalWrite(trigger_frente, LOW);
        duracion_frente = pulseIn(echo_frente, HIGH); 
        frente = duracion_frente/29/2;
      }

      if (frente > 9) {

        analogWrite(vel_motor_izq, 140); //Avanza 500 Ms para evitar el caso en el que no haya pared a a derecha tampoco
        analogWrite(vel_motor_der, 155);
      
        adelante();
      
        delay(500);
        
      }
  
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
  
      /* ---- Una vez que giró sobre su eje, que NO siga girando a la izquierda al no tener pared a la izquierda y se salga del laberinto ---- */
      while (izquierda > 10 && frente > 7){ //mientras que no haya nada a la izquierda que avance teniendo de referencia la derecha
    
        digitalWrite(trigger_frente, LOW); //se declaran las respectivas entradas y salidas de señales del ultrasónico y almacenada por la variable del sensor
        delayMicroseconds(2);              // que convierte la velocidad del sonido que es de 340 m/s por 29 microsengundos por cm, como la señal va y viene 
        digitalWrite(trigger_frente, HIGH); //ese tiempo es la mitad  siendo sensor = tiempo/29/2
        delayMicroseconds(5);
        digitalWrite(trigger_frente, LOW);
        duracion_frente = pulseIn(echo_frente, HIGH); //Estos calculos siguen con los otros sensores
        frente = duracion_frente/29/2;
        
        digitalWrite(trigger_izq, LOW);
        delayMicroseconds(2);
        digitalWrite(trigger_izq, HIGH);
        delayMicroseconds(5);
        digitalWrite(trigger_izq, LOW);
        duracion_izq = pulseIn(echo_izq, HIGH);
        izquierda = duracion_izq/29/2;
        
        digitalWrite(trigger_der, LOW);
        delayMicroseconds(2);
        digitalWrite(trigger_der, HIGH);
        delayMicroseconds(5);
        digitalWrite(trigger_der, LOW);
        duracion_der = pulseIn(echo_der, HIGH);
        derecha = duracion_der/29/2;

        analogWrite(vel_motor_izq, 0); //se bloquea para inicializar las entradas con pulso 0 o apagado
        analogWrite(vel_motor_izq, 0);
        digitalWrite(i1, LOW);
        digitalWrite(i2, LOW);
        digitalWrite(d1, LOW);
        digitalWrite(d2, LOW);
    
        if(derecha > 6 && derecha < 12){
        
            analogWrite(vel_motor_izq, 160); 
            analogWrite(vel_motor_der, 135); 
               
            adelante();
              
        } else if(derecha <= 6 || derecha > 900) {
  
            analogWrite(vel_motor_izq, 85);
            analogWrite(vel_motor_der, 135); 
         
            adelante();
          
        } else if(derecha >= 12 && derecha <= 80){
                                              
            analogWrite(vel_motor_izq, 255);
            analogWrite(vel_motor_der, 60);
            
            adelante();
  
        }
      }
    }
  }
}
