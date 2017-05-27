#ifndef Position_h
#define Position_h
#include "quaternionFilters.h"
#include "MPU9250.h"
// See also MPU-9250 Register Map and Descriptions, Revision 4.0,
// RM-MPU-9250A-00, Rev. 1.4, 9/9/2013 for registers not listed in above
// document; the MPU9250 and MPU9150 are virtually identical but the latter has
// a different register map

enum principalAxes{
  ROLL = 0,
  PITCH = 1,
  YAW = 2
};
class Position{
	private:
    MPU9250 IMU;
    void loadGyroData();
    void loadAccelData();
    void loadMagData();
    void loadPrincipalAxes();
	public:
    void getReady();
    float* getPrincipalData();
    float readAccel(char);
    float readGyro(char);
    float readMag(char);
};
#endif
