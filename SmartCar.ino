

int optFaros = 12;
int optSwitch = 11;
int btnLeds = 10;
int ledRight = 9;
int ledLeft = 8;
int faros = 7;


int conLed = 0;
boolean banFarosApagados = true;
boolean banBtn = false;
 

int pulsador=0;              //almacena el estado del botón
int estado=0;                //0=led apagado, 1=led encendido
int pulsadorAnt=0;

int timeFaros=0;

int buffEstrobo = 0;

boolean encender = true;
boolean apagar  = false;
boolean banFaros = false;

const int tiempoAntirebote =10;
int cuenta =0;          //Guarda el numero de veces que el boton ha sido presionado
int estadoBoton;
int estadoBotonAnterior;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(btnLeds, INPUT);
  pinMode(optFaros, INPUT);
  pinMode(faros, OUTPUT);
  pinMode(optSwitch, INPUT);
  
  digitalWrite(faros, encender);
  digitalWrite(ledLeft, encender);
  digitalWrite(ledRight, encender);

  Serial.begin(9600); //Iniciamos la comunicación  serial
}

// the loop function runs over and over again forever
void loop() {
  //esta apagado el reley
  //digitalWrite(otro, encender);

  if(digitalRead(optSwitch) == LOW && digitalRead(optFaros) == LOW)
  {
    banFarosApagados = true;
    timeFaros = 0;
  }
  else if(digitalRead(optSwitch) == LOW && digitalRead(optFaros) == HIGH)
  {
    banFarosApagados = false;
    if(timeFaros >= 30000 )
    {
      digitalWrite(faros, apagar);
      digitalWrite(ledLeft, apagar);
      digitalWrite(ledRight, apagar);
      banBtn = false;
      buffEstrobo = 0; 
      banFarosApagados = true;
    }
    delay(1);
    timeFaros += 1;
  }
  else
  {
    digitalWrite(faros, encender);
    digitalWrite(ledLeft, encender);
    digitalWrite(ledRight, encender);
    timeFaros = 0;
    banFarosApagados = false;
  }

  estadoBoton =digitalRead (btnLeds);              //leemos el estado del boton
  if (estadoBoton  != estadoBotonAnterior) {     //si hay cambio con respeto al estado 
    if (antirebote (btnLeds)){                    //checamos  si esta preionado y si lo esta
      banBtn = true;
      buffEstrobo++;
      if(buffEstrobo > 5){
          buffEstrobo = 0;
      }  
      Serial.println (buffEstrobo);       
    }
  }
  
  estadoBotonAnterior = estadoBoton;      // guardamos el estado del boton
  
  if(banBtn){
     estrobos(buffEstrobo, ledLeft, ledRight);
  }
  

  /*

  pulsador = digitalRead(btnLeds); //lee si el botón está pulsado
  
  if(( pulsador ==HIGH)&&(pulsadorAnt==LOW)){  //si el boton es pulsado y antes no lo estaba
    estado=1-estado;
    delay(200);               //pausa de 40 ms
    TimeFaors(200);
  }
  pulsadorAnt=pulsador;      //actualiza el nuevo estado del boton        
  
  if(estado==1) {            //si el estado es 1
     estrobos(buffEstrobo, ledLeft, ledRight);
     pulsadorAnt = LOW;
  }
  else if(!banFarosApagados){                      //si el estado es 0
    digitalWrite(ledLeft, encender);
    digitalWrite(ledRight, encender);
    buffEstrobo++;
    if(buffEstrobo > 2)
      buffEstrobo = 1;
  }
*/
}

void estrobos(int op, int reley1, int reley2){
    conLed++;
    if(conLed == 5){
      conLed = 0;
    }
    digitalWrite(reley1, apagar);
    digitalWrite(reley2, apagar);
    switch(op){
      case 0:
      case 2:
      case 4:
        digitalWrite(ledLeft, encender);
        digitalWrite(ledRight, encender);
        banBtn=false;
      break;  
      //Estrobos
        case 1:
            for (int i = 0; i < 2; ++i)
            {
                digitalWrite(reley1, encender);
                delay(100);
                digitalWrite(reley1, apagar);
                delay(100);
                TimeFaors(200);  
            }
            for (int i = 0; i < 2; ++i)
            {
                digitalWrite(reley2, encender);
                delay(100);
                digitalWrite(reley2, apagar);
                delay(100);
                TimeFaors(200);
            }
        break;
        //
        case 3:
            for (int i = 0; i < 2; ++i)
            {
                digitalWrite(reley1, encender);
                digitalWrite(reley2, encender);
                delay(70);
                digitalWrite(reley2, apagar);
                digitalWrite(reley1, apagar);
                delay(70);
                TimeFaors(140);
            }
            delay(300);
            TimeFaors(300);
        break;
        case 5:
            digitalWrite(reley2, encender);
            delay(100);
            digitalWrite(reley2, apagar);
            delay(100);
            digitalWrite(reley1, encender);
            delay(100);
            digitalWrite(reley1, apagar);
            delay(200);
            TimeFaors(500);
            
        break;      
    }
}
void TimeFaors(int tiempo){
  if(!banFarosApagados){
    timeFaros += tiempo;
  }
}

/*Función antirebote*/
boolean antirebote  (int pin ) {
  int  contador =0;
  boolean estado;            // guarda el estado del boton 
  boolean estadoAnterior;    // guarda el ultimo estado del boton 

  do {
    estado = digitalRead (pin);
    if (estado != estadoAnterior ){  // comparamos el estado actual 
      contador = 0;                   // reiniciamos el contador 
      estadoAnterior = estado;
    }
    else{
      contador = contador +1;       // aumentamos el contador en 1
    }
    delay (1);
    TimeFaors(1);
  }
  while (contador < tiempoAntirebote);
  return estado;
}


