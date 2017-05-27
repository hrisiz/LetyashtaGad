#ifndef Quadcopter_h
#define Quadcopter_h

#include "Arduino.h"
#include "Motor.h"
#include "Position.h"

enum Motors{
  FRONT_LEFT = 0,
  FRONT_RIGHT = 1,
  BACK_LEFT = 2,
  BACK_RIGHT = 3
};
class Quadcopter{
  private:
    Motor motor[4];
    Position position;
    float currentPrincipalAxes[3];
    bool calibrateQuadcopterMotors();
    void configMotorsTimer();
    void configPositionTimer();
    void getStartPosition();
  public:
    Quadcopter();
    bool getReady();
    bool setQuadcopterPosition(short, short);
    Motor getMotor(int);
    Position getPosition();
    void setDronePos(float, float, float);
};
#endif
