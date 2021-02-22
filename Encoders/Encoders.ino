#include <AFMotor.h>
#define encoder1 A0
#define encoder2 A1

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);

uint8_t contador;

float rpm1;
float rpm2;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  motor4.run(FORWARD);
  motor3.run(FORWARD);
  motor4.setSpeed(120);
  motor3.setSpeed(120);
  pinMode(encoder1,INPUT);
  pinMode(encoder2,INPUT);
}
 
void loop() {
   
  rpm1 = calcular_rpm(encoder1);
  rpm2 = calcular_rpm(encoder2);
  Serial.print("RPM:  ");
  Serial.print(rpm1);
  Serial.print("   RPM:  ");
  Serial.println(rpm2);
  /*}
  int rpm1_prom = (rpm1[0]+rpm1[1]+rpm1[2])/3;
  Serial.print("RPM:  ");
  Serial.println(rpm1_prom); 
  */

  /*boolean flanco = detectaFlancoAscendente(encoder1);
  if (flanco == HIGH)
    Serial.println(1);
  if (flanco == LOW)
    Serial.println(0);*/
 
}


float calcular_rpm(int pin){
  unsigned long duracion1[] = {0,0,0,0};
  for (int k=0;k<=3;k++){
    duracion1[k] = pulseIn(pin,LOW);  
  }
  float promedio1 = (duracion1[0]+duracion1[1]+duracion1[2])/(3000);   //tiempo en ms
  float promedio2 = (promedio1 + duracion1[3])/2000;                   //tiempo en s
  //Serial.println(promedio2);
  float rpm = (0.5235*9549.3)/(3*promedio2);                            // rad/s  ->> RPM      
  //Serial.print("RPM:  ");
  //Serial.println(rpm);
  return rpm;
}

boolean detectaFlancoAscendente(int pin) {
  static boolean anterior_estado = digitalRead(pin);
  boolean estado = digitalRead(pin);

  if ((anterior_estado != estado) && (estado == HIGH)) {
    anterior_estado = estado ;
    return true;
  }
  else {
    anterior_estado = estado;
return false;
  }
}

int detectaFlanco(int pin) {
  //Devuelve 1 flanco ascendente, -1 flanco descendente y 0 si no hay nada
  static boolean anterior_estado = digitalRead(pin);
  boolean estado = digitalRead(pin);

  if (anterior_estado != estado) {
    if (estado == HIGH) {
   anterior_estado = estado;
      return 1;
    }
    else {
      anterior_estado = estado;
      return -1;
    }
  }
  else {
    return 0;
  }
}

boolean detectaFlancoDescendente(int pin) {
  static boolean anterior_estado = digitalRead(pin);
  boolean estado = digitalRead(pin);

  if ((anterior_estado != estado) && (estado == LOW)) {
    anterior_estado = estado;
    return true;
  }
  else {
    anterior_estado = estado;
    return false;
  }}
