/* Miguel García
 *  17560
 *  Mini proyecto
 */

//--------------------------- Librerías---------------------------------------------------
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <AFMotor.h>
#include <Servo.h> 
#include <AccelStepper.h>

Servo servo1;
Servo servo2;
AF_DCMotor motor4(4);
AF_DCMotor motor3(3);
AF_Stepper motor1(200, 1);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//--------------------------- Variables ---------------------------------------------------
int recibir[]={0,90,0,0,0};
int contador = 0;
int vel_dc = 0;
int memoria_dc = 0;

//--------------------------- Funciones ---------------------------------------------------
void forwardstep1() {   // you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
  motor1.onestep(FORWARD, SINGLE);
}
void backwardstep1() {  
  motor1.onestep(BACKWARD, SINGLE);
}
AccelStepper stepper1(forwardstep1, backwardstep1);

//----------------------------- Setup ---------------------------------------------------
void setup() {
  Serial.begin(9600);               // UART
  mlx.begin();                      // I2C - sensor
  servo1.write(90);                 // Servos
  servo2.write(0);  
  servo1.attach(9);
  servo2.attach(10);
  stepper1.setSpeed(30);      // Stepper
  stepper1.setAcceleration(200.0);
  //stepper1.moveTo(500);
}
 
void loop() {
  //Serial.println(mlx.readAmbientTempC());
  //Serial.print(mlx.readObjectTempC()); 
  
 if(Serial.available()>3){      // recibimos los datos del serial y los guardamos en el array
   if(Serial.read()==0xFF){
       recibir[1] = Serial.read(), recibir[2] = Serial.read(); recibir[3] = Serial.read();
       recibir[4] = Serial.read();
       recibir[5] = Serial.read();
       Serial.println(mlx.readAmbientTempC());
       Serial.println(mlx.readObjectTempC());
       
       // stepper
       recibir[3] = map(recibir[3],0,200,-2000,2000);
       stepper1.moveTo(recibir[3]);
       // DC
       recibir[5] = map(recibir[5],30,100,140,255);
       if (recibir[4] == 1){
        if (memoria_dc == 3){
          motor4.run(RELEASE);
          motor3.run(RELEASE);
          delay(200);
        }
        if (recibir[4] == 1){
          motor4.setSpeed(recibir[5]);
          motor3.setSpeed(recibir[5]);
          motor4.run(FORWARD);
          motor3.run(FORWARD);
          memoria_dc = 1;
        }

       }
       else if (recibir[4] == 2){
        motor4.run(RELEASE);
        motor3.run(RELEASE);
        delay(200);
       }
       else if (recibir[4] == 3){
        if (memoria_dc == 1){
          motor4.run(RELEASE);
          motor3.run(RELEASE);
          delay(200);
        }
        if (recibir[4] == 3){
          motor4.run(BACKWARD);
          motor3.run(BACKWARD); 
          motor4.setSpeed(recibir[5]);
          motor3.setSpeed(recibir[5]);
          memoria_dc = 3;
        }
       }
       
       Serial.flush();
     }
 }

  servo1.write(recibir[1]);
  servo2.write(recibir[2]);
  stepper1.run();
  delay(15);
  contador++; 
}
