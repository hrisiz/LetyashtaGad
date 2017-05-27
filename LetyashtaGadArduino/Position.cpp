#include "Position.h"

void Position::loadAccelData(){
  IMU.readAccelData(IMU.accelCount);  
  IMU.getAres();
  IMU.a[0] = (float)IMU.accelCount[0]*IMU.aRes;
  IMU.a[1] = (float)IMU.accelCount[1]*IMU.aRes; 
  IMU.a[2] = (float)IMU.accelCount[2]*IMU.aRes;
}
void Position::loadGyroData(){
  IMU.readGyroData(IMU.gyroCount);
  IMU.getGres();
  IMU.g[0] = (float)IMU.gyroCount[0]*IMU.gRes;
  IMU.g[1] = (float)IMU.gyroCount[1]*IMU.gRes;
  IMU.g[2] = (float)IMU.gyroCount[2]*IMU.gRes;
}
void Position::loadMagData(){
  IMU.readMagData(IMU.magCount);  // Read the x/y/z adc values
  IMU.getMres();
  IMU.magbias[0] = +470.;
  IMU.magbias[1] = +120.;
  IMU.magbias[2] = +125.;

  IMU.m[0] = (float)IMU.magCount[0]*IMU.mRes*IMU.magCalibration[0] - IMU.magbias[0];
  IMU.m[1] = (float)IMU.magCount[1]*IMU.mRes*IMU.magCalibration[1] - IMU.magbias[1];
  IMU.m[2] = (float)IMU.magCount[2]*IMU.mRes*IMU.magCalibration[2] - IMU.magbias[2];
}
void Position::loadPrincipalAxes(){
  loadAccelData();
  loadGyroData();
  loadMagData();
  IMU.updateTime();
  MahonyQuaternionUpdate(IMU.a[0], IMU.a[1], IMU.a[2], IMU.g[0]*DEG_TO_RAD,
                         IMU.g[1]*DEG_TO_RAD, IMU.g[2]*DEG_TO_RAD, IMU.m[1],
                         IMU.m[0], IMU.m[2], IMU.deltat);
  IMU.particleAxes[YAW]   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ() *
                *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1) * *(getQ()+1)
                - *(getQ()+2) * *(getQ()+2) - *(getQ()+3) * *(getQ()+3));
  IMU.particleAxes[PITCH] = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ() *
                *(getQ()+2)));
  IMU.particleAxes[ROLL]  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2) *
                *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1) * *(getQ()+1)
                - *(getQ()+2) * *(getQ()+2) + *(getQ()+3) * *(getQ()+3));
  IMU.particleAxes[PITCH] *= RAD_TO_DEG;
  IMU.particleAxes[YAW]   *= RAD_TO_DEG;
  // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
  //  8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
  // - http://www.ngdc.noaa.gov/geomag-web/#declination
  IMU.particleAxes[YAW]  -= 4.8;
  IMU.particleAxes[ROLL]  *= RAD_TO_DEG;
}
void Position::getReady(){
  byte c = IMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  if (c != 0x71) // WHO_AM_I should always be 0x68
  {
    Serial.println("FAIL1!");
    Serial.println(c,HEX);
    while(1);
  }
  IMU.MPU9250SelfTest(IMU.SelfTest);
  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  IMU.initMPU9250();
  byte d = IMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
  if (d != 0x48){
    Serial.println("FAIL2");
    while(1);
  }
  IMU.initAK8963(IMU.magCalibration);
}
float* Position::getPrincipalData(){
  loadPrincipalAxes();
  return IMU.particleAxes;
}
float Position::readAccel(char axis){
  loadAccelData();
  return IMU.a['x'-axis];
}
float Position::readGyro(char axis){
  loadGyroData();
  return IMU.g['x'-axis];
}
float Position::readMag(char axis){
  loadMagData();
  return IMU.m['x'-axis];
}
