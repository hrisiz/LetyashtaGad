#include "Quadcopter.h"

Quadcopter::Quadcopter(){
  
}

Motor Quadcopter::getMotor(int motor_number){
  return this->motor[motor_number];
}

Position Quadcopter::getPosition(){
  return this->_position;
}


