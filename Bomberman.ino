#include <Servo.h>

Servo servo2;
Servo servo1;

Servo braco1;
Servo braco2;
Servo braco3;
Servo garra4;


 
 int echoPin = 13; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
 int trigPin = 12; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
 

int distancia = 100; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING


 
const int echoPin2 = 5; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin2 = 6; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
 

int distancia2; //VARIÁVEL DO TIPO INTEIRO
String result2; //VARIÁVEL DO TIPO STRING


#define led 7


//variavel que guardadara as cores
char cor;
char cor2;

const int servoPin1 = 9;
const int servoPin2 = 8;

int contador = 50;

#define pinS0 8
#define pinS1 9
#define pinS2 5
#define pinS3 4
#define pinOut 3

#define pinS0T 8
#define pinS1T 9
#define pinS2T A1
#define pinS3T 0
#define pinOutT A0

unsigned int red = 0;
unsigned int green = 0;
unsigned int blue = 0;
unsigned int white = 0;

unsigned int red2 = 0;
unsigned int green2 = 0;
unsigned int blue2 = 0;
unsigned int white2 = 0;


void cores(); //Inicialização da função


// referenciando as funçoes para poder chamalas de qualquer lugar do codigo
void identificar_cor(uint16_t r, uint16_t g, uint16_t b, uint16_t TemperaturaDaCor, uint16_t LUX,uint16_t c);
void SegueRetoMotorDireito();
void SegueRetoMotorEsquerdo();
//extern void direitaVerde();
//extern void esquerdaVerde();
void Lerldr();
void reto();
void sensorDeCor();
void desliga();
void condicao();
void MeiaVolta();
void Distancia();
void configCor();
void hcsr04(int echoPin, int trigPin);

void setup() {
  Serial.begin(9600);
 
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT); 
  
  pinMode(echoPin2, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin2, OUTPUT);
  

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
/*
  braco1.attach(A2);
  braco2.attach(A5);
  braco3.attach(A4);
  garra4.attach(A3);


  braco1.write(180);
  braco2.write(0);
  braco3.write(0);
  garra4.write(0);
*/
  
  pinMode(led, OUTPUT);
 
  digitalWrite(led, HIGH);

  pinMode(pinS0, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinOut, INPUT);
  
  pinMode(pinS0T, OUTPUT);
  pinMode(pinS1T, OUTPUT);
  pinMode(pinS2T, OUTPUT);
  pinMode(pinS3T, OUTPUT);
  pinMode(pinOutT, INPUT);

  digitalWrite(pinS0, HIGH);
  digitalWrite(pinS1, LOW);

   digitalWrite(pinS0T, HIGH);
   digitalWrite(pinS1T, LOW);
   configCor();
}

void loop() {
  
  sensorDeCor();
 
  if(contador < 10){
  if(distancia < 15){
    servo2.write(65);
    servo1.write(65);
    Serial.println("meia volta pro outro lado");
    delay(2100);
    reto();
    delay(2300);

    MeiaVolta();
    delay(2000);

    reto();
    delay(5000);
    
    MeiaVolta();
    delay(2300);
    
   
    while(!(cor == 'p')){
    
      sensorDeCor();
      reto();
    }
    servo2.write(65);
    servo1.write(65);
    Serial.println("meia volta pro outro lado");
    delay(2000);
    condicao();
  }
  }
  else{
    contador = contador - 1;
    Serial.print("contador "); //IMPRIME O TEXTO NO MONITOR SERIAL
      Serial.print(contador);
  }
    
  
    
      
  condicao();

  hcsr04(echoPin,trigPin); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  Serial.print("Distancia "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(distancia); ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
  Serial.println("cm"); //IMPRIME O TEXTO NO MONITOR SERIAL


 
}



void cores() { //funçao responsavel por definir a cor que o sensor de luminosidade está lendo
   if (blue < 60 && red < 60 && green < 60) { //detecção da cor branca
    Serial.println("Branco");
    cor = 'b';
  }
  
  else if (green < 100 && blue < 146 && red > 115 ) { 
    Serial.println("Verde");
    cor = 'v';
  }

  else/* if (green > 100 &&  blue > 100 && red > 100 ) */{ 
    Serial.println("Preto");
    cor = 'p';
  }
  
  
}
void cores2() { //funçao responsavel por definir a cor que o sensor de luminosidade está lendo
  if ( blue2 < 60 && red2 < 60 && green2 < 60) { //detecção da cor branca
    Serial.println("Branco2");
    cor2 = 'b';
    
  }
  
  else if (blue2 < green2 && red2 < green2 && green2 < 100 && red2 > 55 ) { //detecção da cor azul
    Serial.println("Verde2");
    cor2 = 'v';
    // verde R2: 57 G2: 70 B2: 58
    //verde no preto R2: 56 G2: 82 B2: 55
  }

  else{ //detecção da cor verde
    Serial.println("Preto2");
    cor2 = 'p';
  }
}


void condicao(){
   if(cor2 == 'v' && cor == 'v'){
      MeiaVolta();
      delay(3000);

      while(!(cor == 'p')){
        MeiaVolta();
        sensorDeCor();
  
      }
    }
   else if(cor == 'v' && cor2 != 'v'){
     
      SegueRetoMotorDireito();
      delay(500);

      cores2();
      cores();
      if(cor == 'v' && cor2 != 'v'){
        reto();
        delay(800);
        Serial.println("segue reto motor direito");
        SegueRetoMotorEsquerdo();
        delay(4500);
        reto();
        delay(1000);
      }
      
    }
    else if(cor2 == 'v' && cor != 'v'){
      
      SegueRetoMotorEsquerdo();
      delay(500);

      cores2();
      cores();
      
      if(cor2 == 'v' && cor != 'v'){
      Serial.println("segue reto motor esquerdo");

      reto();
      delay(1000);
      SegueRetoMotorDireito(); 
      delay(4500);

      reto();
      delay(1000);
      }
    }

  else if (cor == 'p' && cor2 == 'b') { 
    Serial.println("1"); 
     SegueRetoMotorEsquerdo();
    
  }

  else if (cor == 'b' && cor2 == 'p') {
    Serial.println("2"); 
    SegueRetoMotorDireito();
    }
  
  else if (( cor == 'p' && cor2 == 'p' ) || (cor == 'b' && cor2 == 'b' )) {
    Serial.println("3"); 
    reto(); 
    }
  else if(( cor == 'c' && cor2 == 'c' )){
    parteDecima();
  }
}

  

  //*desliga

  
void desliga() {
  
  servo2.write(90);
  servo1.write(90);
  Serial.println("desliga");
}

//**reto


void reto() {
  servo2.write(75);
  servo1.write(105);
  Serial.println("reto");
}

//**segue reto

// liga um motor com velocidade normal e o outro mais lento(isso serve para fazer curvas ou asertar a linha
void SegueRetoMotorDireito() {
  servo2.write(75);
  servo1.write(70);

  Serial.println("direita");
  
}

void SegueRetoMotorEsquerdo() {
  servo2.write(105);
  servo1.write(110);
  Serial.println("esquerda");
}

//*meia volta
void MeiaVolta(){
  servo2.write(115);
  servo1.write(115);
  Serial.println("meia volta");
}



void hcsr04(int echoPin, int trigPin){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE

    unsigned long duration = pulseIn(echoPin,HIGH);
    distancia = duration * 0.0343 / 2;
 }

 void sensorDeCor(){
   digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  red = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
  
  //Sem filtro
  digitalWrite(pinS2, HIGH);
  white = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Azul
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  blue = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Verde
  digitalWrite(pinS2, HIGH);
  green = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, LOW);
  red2 = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);
  
  //Sem filtro
  digitalWrite(pinS2, HIGH);
  white2 = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Azul
  digitalWrite(pinS2, LOW);
  digitalWrite(pinS3, HIGH);
  blue2 = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  //Verde
  digitalWrite(pinS2, HIGH);
  green2 = pulseIn(pinOut, digitalRead(pinOut) == HIGH ? LOW : HIGH);

  Serial.print("Vermelho :");
  Serial.print(red);

  Serial.print(" Verde : ");
  Serial.print(green);

  Serial.print(" Azul : ");
  Serial.print(blue);

  Serial.print(" Branco : ");
  Serial.print(white);
  Serial.println();

  Serial.print("Vermelho :");
  Serial.print(red2);

  Serial.print(" Verde : ");
  Serial.print(green2);

  Serial.print(" Azul : ");
  Serial.print(blue2);

  Serial.print(" Branco : ");
  Serial.print(white2);
  Serial.println();
  
  cores2();
  cores(); //chamada da função cores()
 }

  void parteDecima(){
    // millis()
    reto();
    hcsr04(echoPin,trigPin);

    if(distancia < 5){
      braco1.write(180);
  }
}

 void configCor(){}
