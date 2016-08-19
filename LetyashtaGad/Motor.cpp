#include "Motor.h"

Motor::Motor(int id, int type,int binary){
  this->id = id;
  this->type = type;
  this->binary = binary;
  switch(type){
    case 1:
      this->frequency = 50;
      this->current_power = 1;
      this->max_motor_power = 25;
      this->min_motor_power = 12; //12
      this->up_down_step = 1; //1
      this->off_power = 10;//10
      break;
    case 2:
      this->frequency = 500;
      this->current_power = 125;
      this->max_motor_power = 200;
      this->min_motor_power = 150;
      this->up_down_step = 5;
      this->off_power = 125;
      break;
    case 3:
      this->frequency = 50;
      this->current_power = 1;
      this->max_motor_power = 26;
      this->min_motor_power = 13; //13
      this->up_down_step = 1; // 1
      this->off_power = 11;//11
      break;
  }
}

void Motor::change_power(int next_power){
  if(this->type == 3){
    Serial.println((this->id/2));
    Serial.println(next_power);  
  }else{
    analogWrite(this->id,next_power);
  }
}

void Motor::set_motor_power(int next_power){
  if(next_power < this->current_power){
     if(next_power < this->off_power){
       next_power = this->off_power; 
    }
    for(int counter = this->current_power; counter > next_power; counter--){
      change_power(counter);
    }
  }else{
     if(next_power > this->max_motor_power){
       next_power = this->max_motor_power; 
    }
    for(int counter = current_power; counter < next_power; counter++){
      change_power(counter);
    }        
  }
  change_power(next_power);
  this->current_power = next_power;   
}

void Motor::up_motor_power(){
  int next_power = (this->current_power + this->up_down_step);
  if(next_power > this->min_motor_power){
    this->set_motor_power(next_power);
  }else{
    this->set_motor_power(this->min_motor_power);
  }
}

void Motor::low_motor_power(){
  int next_power = (this->current_power - this->up_down_step);
  if(next_power > this->min_motor_power){
    this->set_motor_power(next_power);
  }else{
    this->set_motor_power(this->min_motor_power);
  }
}

void Motor::init_motor(){
  if(this->type == 1){
    this->set_motor_power(this->max_motor_power);
  }else if(this->type == 2){
    this->set_motor_power(this->off_power);        
  }
}

void Motor::motor_start_power(){
  this->set_motor_power(this->off_power);
}

int Motor::check_power(){
  return  this->current_power;
}

int Motor::get_id(){
  return  this->id;
}

boolean Motor::is_max(){
  return this->current_power >= this->max_motor_power;
}

