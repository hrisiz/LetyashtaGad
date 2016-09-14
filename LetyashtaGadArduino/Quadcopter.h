#ifndef Quadcopter_h
#define Quadcopter_h

#include "Motor.h"
#include "Position.h"

class Quadcopter {
  private:
    Motor motor[4];
    Position _position;
    bool setMotorsSignal(int, int);
    bool calibrateQuadcopterMotors();
  public:
    Quadcopter();
    bool getReady();
    bool setQuadcopterPosition(short, short);
    Motor getMotor(int);
    Position getPosition();
};
#endif
