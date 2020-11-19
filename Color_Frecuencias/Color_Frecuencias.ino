#include <Servo.h>

// Sensor de Color
//
//    Arduino   TCS230 SENSOR COLOR
//     10         OUT
//     11         S3
//     12         S2
//      9         S1
//      8         S0
//      5V        VCC
//      GND       GND
//
// 
//


#define S0 8
#define S1 9
#define S2 12
#define S3 11
#define sensorSalida 10
int Rojo_Frec = 0;
int Verde_Frec = 0;
int Azul_Frec = 0;

String R = " "; 
String G = " "; 
String B = " "; 
String d = " "; 
String T = " "; 
String VS;
const int pinecho = 3;
const int pintrigger = 2;


unsigned int tiempo, distancia;

Servo servo_A; 
Servo servo_B;


void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorSalida, INPUT);

  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);

  servo_A.attach(6);
  servo_B.attach(4); 
  

                           // Configura la escala de Frecuencia en 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {                          
                          // Configura el filtor ROJO para tomar lectura
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  delay(100);
  Rojo_Frec= pulseIn(sensorSalida, LOW);
  //Serial.print(" R= "); Serial.print(Rojo_Frec);
  delay(100);
                            // Configura el filtor VERDE para tomar lectura
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  delay(100);
  Verde_Frec = pulseIn(sensorSalida, LOW);
  //Serial.print(" V= "); Serial.print(Verde_Frec);
  delay(100);
                           // Configura el filtor AZUL para tomar lectura
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  delay(100);
  Azul_Frec = pulseIn(sensorSalida, LOW);
  //Serial.print(" A= "); Serial.print(Azul_Frec);
  delay(100);

 /* servo_B.write(70);
  delay(1000); 
  servo_B.write(110);
  delay(1000);*/
                  //Valores obtenidos en la calibracion del sensor, son propios de cada usuario 
                  
 if (Rojo_Frec > 240 && Verde_Frec > 325 && Azul_Frec > 90) {
  //Serial.print(" . *** CANELO **");
  //Serial.print(distance()); 
  //Serial.print(" cm"); 
  servo_A.write(180); 
  servo_B.write(70); 
  delay(1000);
  servo_A.write(0);
  delay(1000);
  
  R = Rojo_Frec; 
  G = Verde_Frec; 
  B = Azul_Frec; 
  d = distance(); 
  VS = R + "," + G + "," + B +"," + d + "," + "C" + "\n"; 
  Serial.print(VS);
  
 }
 //if (Rojo_Frec > 80 && Verde_Frec > 100 && Azul_Frec < 80)  Serial.print(" . *** AZUL **");
 if (Rojo_Frec > 240 && Verde_Frec > 230&& Azul_Frec <90)  {
  //Serial.print(" . *** GUERO **");
  //Serial.print(distance()); 
  //Serial.print(" cm"); 
  servo_A.write(180); 
  servo_B.write(110); 
  delay(1000);
  servo_A.write(0);
  delay(1000);
  R = Rojo_Frec; 
  G = Verde_Frec; 
  B = Azul_Frec; 
  d = distance(); 
  VS = R + "," + G + "," + B +"," + d + "," + "G" +"\n"; 
  Serial.print(VS);
  
 }
 //if (Rojo_Frec < 35 && Verde_Frec < 35 && Azul_Frec < 35)  Serial.print(" . *** BLANCO **");
 if (Rojo_Frec > 200 && Verde_Frec > 200 && Azul_Frec <85)  {
  //Serial.print(" . *** NEGRO **");
  servo_A.write(10); 
 }
 else {
  servo_A.write(10);
 }

 //Serial.println("*");
 delay(200);
}

int distance() {
  // ENVIAR PULSO DE DISPARO EN EL PIN "TRIGGER"
  digitalWrite(pintrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pintrigger, HIGH);
  // EL PULSO DURA AL MENOS 10 uS EN ESTADO ALTO
  delayMicroseconds(10);
  digitalWrite(pintrigger, LOW);

  // MEDIR EL TIEMPO EN ESTADO ALTO DEL PIN "ECHO" EL PULSO ES PROPORCIONAL A LA DISTANCIA MEDIDA
  tiempo = pulseIn(pinecho, HIGH);

  // LA VELOCIDAD DEL SONIDO ES DE 340 M/S O 29 MICROSEGUNDOS POR CENTIMETRO
  // DIVIDIMOS EL TIEMPO DEL PULSO ENTRE 58, TIEMPO QUE TARDA RECORRER IDA Y VUELTA UN CENTIMETRO LA ONDA SONORA
  distancia = tiempo / 58;

  return distancia;
  
}
