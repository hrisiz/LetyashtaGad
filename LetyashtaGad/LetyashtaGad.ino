#include<msp430g2553.h>
#include "Drone.h"
                            
int input = -1;
Drone drone;
void establishContact();

void setup() {
  analogFrequency(50);
  pinMode(RED_LED, OUTPUT);  
  
  digitalWrite(RED_LED,HIGH);
  Serial.begin(9600);
  establishContact();
  drone.start();
}

void loop(){
  digitalWrite(RED_LED,LOW);
  input = -1;
  while((input = Serial.read()) <= -1);// 1 - up all motors 2 - low all motors 3 - left 4 -right 5 - forward 6 - back
  Serial.println(input);
  switch(input){
    case '+':
      drone.move(UP);
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '-':
      drone.move(DOWN);
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
     case '5':
       drone.move(MOTOR_STOP);
       break;
     case '8':
       drone.move(FORWARD);
       break;
     case '2':
       drone.move(BACKWARD);
       break;
     case '4':
       drone.move(LEFT);
       break;
     case '6':
       drone.move(RIGHT);
       break;
     case '7':
      drone.one_motor_test(); 
      break;
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    digitalWrite(RED_LED,HIGH);
    delay(300);
    Serial.println("A"); 
    digitalWrite(RED_LED,LOW);
    delay(300);
  }
}
