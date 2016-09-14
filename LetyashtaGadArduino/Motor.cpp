#include "Motor.h"

bool Motor::valueToPPMTime(){
  if(this->value < 80){
    this->value = 0;
    return false;
  }
  int new_ppm = MIN_MOTOR_POWER + this->value;
  if(new_ppm <= MAX_MOTOR_POWER){
    this->ppm_time =  new_ppm;
    return true;
  }else{
    return false;
  }
}

Motor::Motor(){
	this->value = 0;
  this->ppm_time = 0;
}

bool Motor::setValue(int value){
  this->value = value;
  return this->valueToPPMTime();
}

int Motor::getPPMTime(){
  return this->ppm_time;
}

int Motor::getValue(){
  return this->value;
}

