#define vel_motor_izq 10 //controla la velocidad del motor izquierdo (ENA)
#define vel_motor_der 11 //controla la velocidad del motor derecho (ENB)
#define i1 5 //controla el sentido de rotacion del motor izquierdo (IN1)
#define i2 3 //controla el sentido de rotacion del motor izquierdo (IN2)
#define d1 9 //controla el sentido de rotacion del motor derecho (IN4)
#define d2 6 //controla el sentido de rotacion del motor derecho (IN3)
#define opt 2 //sensor óptico infrarrojo para detectar blanco al finalizar el recorrido

int trigger_frente = A4; //controla el impulso enviado al sensor del frente
int echo_frente = A5; //controla el impulso recibido en el sensor del frente

int trigger_izq = A2; //controla el impulso enviado del sensor izquierdo
int echo_izq = A3; //controla el impulso recibido del sensor izquierdo

int trigger_der = A0; //controla el impulso enviado del sensor derecho
int echo_der = A1; //controla el impulso recibido del sensor derecho

//variables para el control del proyecto
long duracion_frente, duracion_izq, duracion_der, derecha, izquierda, frente;
int retraso, giro;
//int referencia_izq;

void setup() {
  pinMode(trigger_frente, OUTPUT);
  pinMode(echo_frente, INPUT);

  pinMode(trigger_izq, OUTPUT);
  pinMode(echo_izq, INPUT);

  pinMode(trigger_der, OUTPUT);
  pinMode(echo_der, INPUT);

  pinMode(vel_motor_izq, OUTPUT);
  pinMode(vel_motor_der, OUTPUT);

  pinMode(i1, OUTPUT); //salida de la señal de arduino para el control del sentido de rotación del motor izquierdo
  pinMode(i2, OUTPUT); //salida de la señal de arduino para el control del sentido de rotación del motor izquierdo
  pinMode(d1, OUTPUT); //salida de la señal de arduino para el control del sentido de rotación del motor derecho
  pinMode(d2, OUTPUT); //salida de la señal de arduino para el control del sentido de rotación del motor derecho

  pinMode(opt, INPUT);

  retraso = 350;
  giro = 500; //funcionaba con 900 - depende de la bateria
  //referencia_izq = 0;
  
  delay(500);

  secuencia_inicial(); //En caso que necesite avanzar al comienzo para entrar al laberinto

}

void loop() {

  /* ---- Detener al detectar blanco con distinto a 1 ---- 
  while(digitalRead(opt) != 1){ //Si el sensor optico detecta negro/no rebota (piso del laberinto) que siga, sino, detener. (0 = blanco, 1 = negro) 
    detener();
  } 
  ------------- fin optico para detener --------------- */
    
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
  
  if(frente > 9 && frente < 900) { //En caso que no haya nada en frente sigue con lo de abajo
    
    if(izquierda > 6 && izquierda < 12){ //en caso de que la pared estuviera entre 7 y 13 cm el robot sigue en linea recta
      
        analogWrite(vel_motor_izq, 160); // 80 es el mínimo con arduino MEGA, 130 genuino 101. con 80 llegan 3.0v y 5.6v con 255
        analogWrite(vel_motor_der, 135); //135 (der) y 160 (izq) son los valores mas parejos medidos con el tester en el driver y con arduino UNO
           
        adelante();
            
    } else if(izquierda >= 12){ //quité "&& izquierda <= 80"
      //en caso que la pared izquierda estuviera a mas o igual a 12 cm y menor a 80 para evitar el error de ultra de valores mayores a 2 mil, 
                                            //el robot aumenta la vel del motor derecho (y detiene el izquierdo) para realizar el giro a la izquierda
        analogWrite(vel_motor_izq, 60);
        analogWrite(vel_motor_der, 255);
        
        adelante();

    } else if(izquierda <= 6 || izquierda > 900){ //Mayor a 1000 en caso que esté muy cerca y falle el sensor y muestre valores muy altos
                                                  
        analogWrite(vel_motor_izq, 160); //de 255
        analogWrite(vel_motor_der, 85);
        
        adelante();
      
    } else if(derecha <= 6 || derecha > 900) { //Mayor a 900 en caso que esté muy cerca y falle el sensor y muestre valores muy altos

        analogWrite(vel_motor_izq, 85);
        analogWrite(vel_motor_der, 135); //de 255
     
        adelante();
    }
    
  } else { //SINO del IF de si no hay nada en frente

    detener();

    digitalWrite(trigger_der, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_der, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigger_der, LOW);
    duracion_der = pulseIn(echo_der, HIGH);
    derecha = duracion_der/29/2;
    
    if(frente < 3 || frente > 900){ //en caso que haya una pared en frente, ver primero si la derecha está libre y girar, caso contrario girar a la izquierda
  
      retroceder();
      
    } else if (derecha > 10){ //valor de 10 para que la derecha sea mas candidata ya que si llegó a esta condición es porq anteriormente a la izquierda no pudo girar
      
      girar_derecha();
      
      /* //Se podría probar esto directamente y tal vez quitando el detener() anterior
        analogWrite(vel_motor_izq, 255);
        analogWrite(vel_motor_der, 60);
        
        adelante();
       */
      
    } else {
  
      girar_izquierda();
      
    }
  }
}
