// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t GyZ;
int16_t gyroRate;
int16_t offset_gyro_z = 0;
int16_t sensitivity = 2000;
int16_t angle;
int16_t angle_deg;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  //Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.write(0x47);  // starting with register 0x47 (GYRO_ZOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,2,true);  // request a total of 2 registers
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //Serial.print(" | GyZ = "); 
  Serial.println(GyZ);
  //delay(333);

  //gyroRate = (GyZ - offset_gyro_z) * sensitivity;
  //angle += gyroRate / 100.0;
  //angle_deg = angle / 360;
  //Serial.print(" Angle = "); 
  //Serial.println(angle_deg);
  //transmit_string ("Current Angle:", 14);
  //transmit_string (angle, 4);
  //USART_Transmit(10); // newline character
  delay(100); // 10 mS delay
}

