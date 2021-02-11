#include <AFMotor.h>
#include <Servo.h> 

Servo servo1;
Servo servo2;
uint8_t i;
void setup() {
  servo1.attach(9);
  servo2.attach(10);

}

void loop() {
  servo1.write(50);     //Ángulos entre 50 y 130 para la dirección 
  delay(1000);            // 50 para izquierda y 130 para derecha
  servo1.write(90);
  delay(1000);
  servo1.write(130);
  delay(1000);
  servo1.write(90);
  delay(1000);

/*  servo2.write(0);  // Ángulo máximo de 90 para el tilt
  delay(1000);
  servo2.write(45);
  delay(1000);
  servo2.write(90);
  delay(1000);
  servo2.write(45);
  delay(1000);  */
}
