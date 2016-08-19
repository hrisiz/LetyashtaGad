#include "Drone.h"

Drone::Drone() : motors({{9,3,FRONT_LEFT_MOTOR_BINARY},{10,1,FRONT_RIGHT_MOTOR_BINARY},{13,3,BACK_LEFT_MOTOR_BINARY},{14,1,BACK_RIGHT_MOTOR_BINARY}}){
}

int Drone::get_opposite_motor(int m_number){
   return (m_number+2 > 3) ? (m_number-2):(m_number+2);
}
void Drone::change_position(char binary,int time){
  char check[4] = {
    binary & FRONT_LEFT_MOTOR_BINARY,
    binary & FRONT_RIGHT_MOTOR_BINARY,
    binary & BACK_LEFT_MOTOR_BINARY,
    binary & BACK_RIGHT_MOTOR_BINARY
  };
//  for(int next = 0; next < 4; next++){
//    if(this->motors[next].is_max() && check[next]){
//      check[next] = 0;
//      check[this->get_opposite_motor(next)+3] = 1;
//    } 
//  }
  if(check[0]){
    FRONT_LEFT_MOTOR.up_motor_power();
  }
  if(check[1]){
    FRONT_RIGHT_MOTOR.up_motor_power();
  }
  if(check[2]){
    BACK_LEFT_MOTOR.up_motor_power();
  }
  if(check[3]){
    BACK_RIGHT_MOTOR.up_motor_power();
  }
//  
//  if(check[4]){
//    FRONT_LEFT_MOTOR.low_motor_power();
//  }
//  if(check[5]){
//    FRONT_RIGHT_MOTOR.low_motor_power();
//  }
//  if(check[6]){
//    BACK_LEFT_MOTOR.low_motor_power();
//  }
//  if(check[7]){
//    BACK_RIGHT_MOTOR.low_motor_power();
//  }
  delay(time);
  if(check[0]){
    FRONT_LEFT_MOTOR.low_motor_power();
  }
  if(check[1]){
    FRONT_RIGHT_MOTOR.low_motor_power();
  }
  if(check[2]){
    BACK_LEFT_MOTOR.low_motor_power();
  }
  if(check[3]){
    BACK_RIGHT_MOTOR.low_motor_power();
  }
//  
//  if(check[4]){
//    FRONT_LEFT_MOTOR.up_motor_power();
//  }
//  if(check[5]){
//    FRONT_RIGHT_MOTOR.up_motor_power();
//  }
//  if(check[6]){
//    BACK_LEFT_MOTOR.up_motor_power();
//  }
//  if(check[7]){
//    BACK_RIGHT_MOTOR.up_motor_power();
//  }
}

void Drone::move(drone_move move){
  switch(move){
    case UP:
      for(int next = 0; next < 4; next++){
        this->motors[next].up_motor_power();
      }
      break;
    case DOWN:
      for(int next = 0; next < 4; next++){
        this->motors[next].low_motor_power();
      }
      break;
    case LEFT:
      this->change_position(GO_LEFT_BINARY,2000);
      break;
    case RIGHT:
      this->change_position(GO_RIGHT_BINARY,2000);
      break;
    case FORWARD:
      this->change_position(GO_FORWARD_BINARY,2000);
      break;
    case BACKWARD:
      this->change_position(GO_BACKWARD_BINARY,2000);
      break; 
    case MOTOR_STOP:
      for(int next = 0; next < 4; next++){
       this->motors[next].motor_start_power();  
      }
      break;
  }
}

void Drone::start(){
 
  //delay(1000);
  //while(input = Serial.read(),  input != 'R');
//  for(i = 0; i < 4; i++){
//    pinMode(motor[i].get_id(), OUTPUT); 
//    motor[i].init_motor();
//  }
  //while(input = Serial.read(),  input != 'S');
  //delay(1000);
  for(int next = 0; next < 4; next++){
    //pinMode(motors[next].get_id(), OUTPUT);
    this->motors[next].motor_start_power();
  } 
}
void Drone::one_motor_test(){
  BACK_RIGHT_MOTOR.up_motor_power();
  //delay(2000);
 // BACK_RIGHT_MOTOR.low_motor_power();
}
