/*
    Programação Pêndulo Invertido 2WD
*/
#include <PID_v1.h>
#include <LMotorController.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

#define MIN_ABS_SPEED 40

MPU6050 mpu;

bool dmpReady = false; // set true if DMP init was successful
uint8_t mpuIntStatus; // holds actual interrupt status byte from MPU
uint8_t devStatus; // return status after each device operation (0 = success, !0 = error)
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q; // [w, x, y, z] quaternion container
VectorFloat gravity; // [x, y, z] gravity vector
float ypr[3]; // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector

//PID
double originalSetpoint = 0;
double setpoint = originalSetpoint;
double input, output;

//adjust these values to fit your own design
double Kp = 0;
double Kd = 0;
double Ki = 0;
PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

double motorSpeedFactorLeft = 0.9;
double motorSpeedFactorRight = 0.9;

//MOTOR CONTROLLER
int ENA = 0, IN1 = 15, IN2 = 13;
int IN3 = 14, IN4 = 12, ENB = 2;

LMotorController motorController(ENA, IN1, IN2, ENB, IN3, IN4, motorSpeedFactorLeft, motorSpeedFactorRight);

void setup()
{
  Serial.begin(9600);
  Wire.setClock(400000);
  Wire.begin();

  mpu.initialize();
  devStatus = mpu.dmpInitialize();

  Serial.println("Testando conexão...");
  Serial.println(mpu.testConnection() ? "Sensor conectado" : "Falha ao conectar ao sensor");

  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  if (devStatus == 0)
  {
    mpu.setDMPEnabled(true);
    dmpReady = true;

    //setup PID
    pid.SetMode(AUTOMATIC);
    pid.SetSampleTime(10);
    pid.SetOutputLimits(-255, 255);
  }
  else
  {
    Serial.print(("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println((")"));
  }
}


void loop()
{
  if (!dmpReady) return;

  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
  {
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    input = ypr[1] * 180 / M_PI;

    //    Serial.println("\n\nX\tY\tZ");
    //    Serial.println(String(ypr[0] * 180/M_PI) + "\t" + String(ypr[1] * 180/M_PI) + "\t" +String(ypr[2] * 180/M_PI));
  }

  pid.Compute();

  if (abs(input) > 30) motorController.stopMoving();
  else motorController.move(output < 0 ? -1.1 * output : -output, MIN_ABS_SPEED);

  //Serial.println("Input\tOutput\tSetpoint");
  //  Serial.println(String(input)+"\t"+String(output)+"\t"+String(setpoint));
}
