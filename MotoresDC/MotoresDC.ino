#include <AFMotor.h>
//#include <AccelStepper.h>

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);
 
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
}
 
void loop() {
  uint8_t i;
    
  motor4.run(FORWARD);
  motor3.run(FORWARD);
  for (i=100; i<255; i++) {
    motor4.setSpeed(i);
    motor3.setSpeed(i);
    Serial.print(i);
    Serial.print("\n");  
    delay(10);
 }
 
  for (i=255; i!=100; i--) {
    motor4.setSpeed(i);
    motor3.setSpeed(i);  
    delay(10);
 }
  Serial.print("Atras \n");

  motor4.run(BACKWARD);
  motor3.run(BACKWARD);
  for (i=100; i<255; i++) {
    motor4.setSpeed(i);
    motor3.setSpeed(i);  
    Serial.print(i);
    Serial.print("\n");  
    delay(10);
    
 }
 
  for (i=255; i!=100; i--) {
    motor4.setSpeed(i);
    motor3.setSpeed(i);  
    delay(10);
 }
  

  Serial.print("Esperar\n");
  motor4.run(RELEASE);
  motor3.run(RELEASE);
  delay(1000);
}
