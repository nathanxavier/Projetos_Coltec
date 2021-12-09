#include<Wire.h>

const int MPU = 0x68;
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
char sendMsg[1000];

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  // Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

  // Configuração
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  // Registrador 0x1C: XA_ST | YA_ST | ZA_ST | AFS_SEL[1:0] | 0 | 0 | 0
  Wire.write(0b00000000);    // Full Scale Range +/- 2G
  // Wire.write(0b00001000); // Full Scale Range +/- 4G
  // Wire.write(0b00010000); // Full Scale Range +/- 8G
  // Wire.write(0b00011000); // Full Scale Range +/- 16G
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Registrador inicial: 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // 6 Acc +2 Temp +6 Gyro

  //Armazena o valor dos sensores nas variaveis correspondentes
  //  for (int i = 0; i < 7; i++) {
  //    Sens[i] = Wire.read() << 8 | Wire.read();
  //  }
  AcX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  sprintf(sendMsg, "0 6 %d %d %d %d %d %d", AcX, AcY, AcZ, GyX, GyY, GyZ);
  Serial.println(sendMsg);
}
