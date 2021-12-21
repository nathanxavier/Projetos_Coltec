#include "BasicLinearAlgebra.h"
#include <math.h>

// Classe de controle dos motores
class ctrlMotor{ 
  public:
    int pin_1, pin_2, enable;
  
    void setPinConfig(int p1, int p2, int en){ // função de configuração dos pinos
      pin_1 = p1;
      pin_2 = p2;
      enable = en;
      
      pinMode(pin_1, OUTPUT);
      pinMode(pin_2, OUTPUT);
      pinMode(enable, OUTPUT);
    }
  
    void move(float uk){ // Gira motor no sentido horário
      int pwm;

      pwm = map(uk, -50, 50, -255, 255);
      if (pwm>0){
        digitalWrite(pin_2, LOW);
        digitalWrite(pin_1, HIGH);
      }
      else if (pwm<0){
        digitalWrite(pin_1, LOW);
        digitalWrite(pin_2, HIGH);
      }
      else{
        digitalWrite(pin_1, HIGH);
        digitalWrite(pin_2, HIGH);
      }
      pwm = abs(pwm);
      if(pwm>255)
        pwm = 255;
      analogWrite(enable, pwm);
    }
};

ctrlMotor Mot1, Mot2, Mot3;
float qX = 0, qY = 0, qtheta = 0;
float theta = 0;
float L = 0.08;        // Distância da roda em CM
float r = 0.25;    // Raio da roda em CM

// Matriz de Rotação
BLA::Matrix<3, 3> R = { cos(theta), -sin(theta),  0,
                        sin(theta), cos(theta),   0,
                        0,          0,            1};

// Cinemática Direta
BLA::Matrix<3, 3> J = { -r/sqrt(3), 0,          r/sqrt(3),
                        r/3.,      -(2*r)/3.,   r/3.,
                        r/(3*L),   r/(3*L),     r/(3*L)};

BLA::Matrix<3, 3> RJ;
BLA::Matrix<3, 1> qPose; // Matriz de estados 
BLA::Matrix<3, 1> Uk; // Matriz de entrada

void setup() {  
  Mot1.setPinConfig(7,8,11);
  Mot2.setPinConfig(5,6,10);
  Mot3.setPinConfig(4,3,9);

  Serial.begin(9600);
}

void loop() {
  //Move Dir 1
  
  qX = 1;
  qY = 0;
  qtheta = 0;

  qPose = {qX, qY, qtheta};
  RJ = R*J;
  
  Invert(RJ);
  
  Uk = RJ*qPose;

  Serial.print("Uk = [");
  Serial.print(Uk(0));
  Serial.print(", ");
  Serial.print(Uk(1));
  Serial.print(", ");
  Serial.print(Uk(2));
  Serial.println("]");
  
  Mot1.move(Uk(0));
  Mot2.move(Uk(1));
  Mot3.move(Uk(2));
  
  delay(10000);
}