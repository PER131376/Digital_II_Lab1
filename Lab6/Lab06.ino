const int boton = PUSH1;
int estado_boton = 0;
int contador = 0;
int bandera1 = 0;
#define RA0 PE_3 
#define RA1 PE_2
#define RA2 PE_1
#define RA3 PD_3
#define RA4 PD_2
#define RA5 PD_1
#define RA6 PD_0
#define RA7 PA_7    //OTRO LADO
void setup() {
  // put your setup code here, to run once:
  pinMode(boton, INPUT_PULLUP);
  pinMode(RA0, OUTPUT);
  pinMode(RA1, OUTPUT);
  pinMode(RA2, OUTPUT);
  pinMode(RA3, OUTPUT);
  pinMode(RA4, OUTPUT);
  pinMode(RA5, OUTPUT);
  pinMode(RA6, OUTPUT);
  pinMode(RA7, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly: 
  estado_boton = digitalRead(boton);
  if(estado_boton == HIGH)
  {
    bandera1 = 1;    
  }
  else
  {
    if(bandera1 == 1)
    {
           contador++;
           bandera1 = 0;
    }
  }
  
  if(contador == 75)
  {
    contador = 0;
  }
  delay(200);
  switch (contador){
    case 0:
      digitalWrite(RA0, LOW);
      digitalWrite(RA1, LOW);
      digitalWrite(RA2, LOW);
      digitalWrite(RA3, LOW);
      digitalWrite(RA4, LOW);
      digitalWrite(RA5, LOW);
      digitalWrite(RA6, LOW);
      digitalWrite(RA7, LOW);
    break;
    case 1:
      digitalWrite(RA0, HIGH);
    break;
    case 12:
      digitalWrite(RA0, LOW);
      digitalWrite(RA1, HIGH);
    break;
    case 25:
      digitalWrite(RA1, LOW);
      digitalWrite(RA2, HIGH);
    break;
    case 35:
      digitalWrite(RA2, LOW);
      digitalWrite(RA3, HIGH);
    break;
    case 45:
      digitalWrite(RA3, LOW);
      digitalWrite(RA4, HIGH);
    break;
    case 55:
      digitalWrite(RA4, LOW);
      digitalWrite(RA5, HIGH);
    break;
    case 65:
      digitalWrite(RA5, LOW);
      digitalWrite(RA6, HIGH);
    break;
    case 75:
      digitalWrite(RA6, LOW);
      digitalWrite(RA7, HIGH);
    break;
  }
}
