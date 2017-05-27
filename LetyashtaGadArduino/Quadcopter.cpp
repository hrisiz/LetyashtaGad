#include "Quadcopter.h"

Quadcopter::Quadcopter(){
  
}

void Quadcopter::configMotorsTimer(){
  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register, change this
  OCR1B = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
}

//void Quadcopter::configPositionTimer(){
//  //Setup Timer2 to fire every 1ms
//  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
//  TCNT2  = 5;         //Reset Timer Count to 5 out of 255
//  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
//  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
//  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
//  TCCR2B = 0x07;        //Timer2 Control Reg B: Timer Prescaler set to 1024
//}


bool Quadcopter::calibrateQuadcopterMotors(){
  bool result = true;
  for(int i = 0; i < 4; i++){
    result &= this->motor[i].setValue(1000);
  }
  delay(1000);
  for(int i = 0; i < 4; i++){
    result &= this->motor[i].setValue(0);
  }
  return result;
}

bool Quadcopter::getReady(){
  
  this->configMotorsTimer();
  this->position.getReady();   
//  this->configPositionTimer();
  return this->calibrateQuadcopterMotors();
}

Motor Quadcopter::getMotor(int motor_number){
  return this->motor[motor_number];
}

Position Quadcopter::getPosition(){
  return this->position;
}

void Quadcopter::setDronePos(float yaw , float pitch , float roll){
  float* axes = position.getPrincipalData();
  Serial.print("Yaw Pitch Roll: "); 
  Serial.print(axes[YAW]);  
  Serial.print(" ");  
  Serial.print(axes[PITCH]);  
  Serial.print(" "); 
  Serial.print(axes[ROLL]);  
  Serial.println(" "); 
//  yaw - axes[YAW];
//  pitch - axes[PITCH];
//  roll - axes[PITCH];
  currentPrincipalAxes[YAW] = yaw;
  currentPrincipalAxes[PITCH] = pitch;
  currentPrincipalAxes[ROLL] = roll;
}

