#include "Motor.h"

void Motor::valueToPPMTime(){
  if(this->value < 80){
    this->value = 0;
  }
  int new_ppm = this->motor_stat_state + this->value;
  if(new_ppm <= motor_max_state)
    this->ppm_time =  new_ppm;
}

void Motor::valueToPPMTime(int new_ppm){
  if(new_ppm <= motor_max_state)
    this->ppm_time = new_ppm;
}


Motor::Motor(int min_p, int max_p){
	this->id = id;
	this->value = 0;
  this->valueToPPMTime();
  this->motor_stat_state = min_p;
  this->motor_max_state = max_p;
}

void Motor::setValue(int value){
  this->value = value;
  this->valueToPPMTime();
}

void Motor::upValueWith(int value){
  this->value += value;
  this->valueToPPMTime();
}

int Motor::getPPMTime(){
  return this->ppm_time;
}

int Motor::getValue(){
  return this->value;
}

