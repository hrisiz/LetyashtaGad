#include<msp430g2553.h>
#define STEP 5
#define UP_DOWN_STEP 10
#define START_POWER 125
#define MAX_MOTOR_POWER 255
#define MIN_MOTOR_POWER 165
class Motor{
  private:
    int id;
    int current_power;
    void change_power(int next_power){
      analogWrite(this->id,next_power);
    }
  public:
    Motor(int id, int power){
      this->id = id;
      this->current_power = power; 
    }
    
    void up_motor_power(int up_with){
      int next_power = this->current_power + up_with;
      if(next_power > MAX_MOTOR_POWER){
         next_power = MAX_MOTOR_POWER; 
      }
      for(int counter = this->current_power; counter < next_power; counter++){
        change_power(counter);
      }
      change_power(next_power);
      this->current_power = next_power;   
    }
    
    void low_motor_power(int low_with){
      int next_power = this->current_power - low_with;
      if(next_power < START_POWER){
         next_power = START_POWER; 
      }
      for(int counter = this->current_power; counter > next_power; counter--){
        change_power(counter);
      }
      change_power(next_power);
      this->current_power = next_power;
    }
    
    void set_motor_power(int next_power){
      if(next_power < this->current_power){
        for(int counter = current_power; counter > next_power; counter--){
          change_power(counter);
        }
      }else{
        for(int counter = current_power; counter < next_power; counter++){
          change_power(counter);
        }        
      }
      change_power(next_power);
      this->current_power = next_power;   
    }
    
    int check_power(){
      return  this->current_power;
    }
    
    int get_id(){
      return  this->id;
    }
};
Motor motors[4] = {{14,START_POWER},
                             {13,START_POWER},
                             {12,START_POWER}, 
                             {10,START_POWER}
                            };

int i = 0;
int input = -1;

void establishContact();

void setup() {
  for(i = 0; i < 4; i++){
    pinMode(motors[i].get_id(), OUTPUT); 
    motors[i].set_motor_power(START_POWER);
  }
  
  pinMode(RED_LED, OUTPUT);  
  
  Serial.begin(9600);
  establishContact();
  
  digitalWrite(RED_LED,HIGH);
  
  while(input = Serial.read(),  input != 'R');
  digitalWrite(RED_LED,LOW);
}

void loop(){
  digitalWrite(RED_LED,LOW);
  input = -1;
  while((input = Serial.read()) == -1);// 1 - up all motors 2 - low all motors 3 - left 4 -right 5 - forward 6 - back
  Serial.println(input);
  switch(input){
    case '1':
      for(i = 0; i < 4; i++){
        if((motors[i].check_power()+UP_DOWN_STEP) > MIN_MOTOR_POWER){
          motors[i].up_motor_power(UP_DOWN_STEP);
        }else{
          motors[i].set_motor_power(MIN_MOTOR_POWER);
        }
      }
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '2':
      for(i = 0; i < 4; i++){
        if((motors[i].check_power()-UP_DOWN_STEP) > MIN_MOTOR_POWER){
          motors[i].low_motor_power(UP_DOWN_STEP);
        }else{
          motors[i].set_motor_power(MIN_MOTOR_POWER);
        }
      }
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '3':
//      if(motors[1].check_power()-STEP <= MIN_MOTOR_POWER || motors[2].check_power()-STEP <= MIN_MOTOR_POWER){
//        if(motors[1].check_power() < motors[2].check_power()){
//          motors[1].up_motor_power(STEP);     
//        }else if(motors[0].check_power() > motors[3].check_power()){
//          motors[3].up_motor_power(STEP);
//        }else{
//          motors[0].up_motor_power(STEP);
//          motors[3].up_motor_power(STEP);
//        }
//      }else{
//        if(motors[1].check_power() < motors[2].check_power()){
//          motors[2].low_motor_power(STEP);          
//        }else if(motors[1].check_power() > motors[2].check_power()){
//          motors[1].low_motor_power(STEP);
//        }else{
//          motors[1].low_motor_power(STEP);
//          motors[2].low_motor_power(STEP);  
//        }
//      }
      
      if(motors[1].check_power() > MIN_MOTOR_POWER)
        motors[1].low_motor_power(STEP);
      if(motors[2].check_power() > MIN_MOTOR_POWER)
        motors[2].low_motor_power(STEP); 
      motors[0].up_motor_power(STEP);
      motors[3].up_motor_power(STEP);  
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '4':
//      if(motors[0].check_power()-STEP <= MIN_MOTOR_POWER || motors[3].check_power()-STEP <= MIN_MOTOR_POWER){
//        if(motors[1].check_power() < motors[2].check_power()){
//          motors[1].up_motor_power(STEP);     
//        }else if(motors[1].check_power() > motors[2].check_power()){
//          motors[2].up_motor_power(STEP);
//        }else{
//          motors[1].up_motor_power(STEP);
//          motors[2].up_motor_power(STEP);
//        }
//      }else{
//        if(motors[0].check_power() < motors[3].check_power()){
//          motors[3].low_motor_power(STEP);          
//        }else if(motors[0].check_power() > motors[3].check_power()){
//          motors[0].low_motor_power(STEP);
//        }else{
//          motors[0].low_motor_power(STEP);
//          motors[3].low_motor_power(STEP);  
//        }
//      }
      if(motors[0].check_power() > MIN_MOTOR_POWER)
        motors[0].low_motor_power(STEP);
      if(motors[3].check_power() > MIN_MOTOR_POWER)
        motors[3].low_motor_power(STEP); 
      motors[1].up_motor_power(STEP);
      motors[2].up_motor_power(STEP);  
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '5':
//      if(motors[0].check_power()-STEP <= MIN_MOTOR_POWER || motors[1].check_power()-STEP <= MIN_MOTOR_POWER){
//        if(motors[2].check_power() < motors[3].check_power()){
//          motors[2].up_motor_power(STEP);     
//        }else if(motors[2].check_power() > motors[3].check_power()){
//          motors[3].up_motor_power(STEP);
//        }else{
//          motors[2].up_motor_power(STEP);
//          motors[3].up_motor_power(STEP);
//        }
//      }else{
//        if(motors[0].check_power() < motors[1].check_power()){
//          motors[1].low_motor_power(STEP);          
//        }else if(motors[0].check_power() > motors[1].check_power()){
//          motors[0].low_motor_power(STEP);
//        }else{
//          motors[0].low_motor_power(STEP);
//          motors[1].low_motor_power(STEP);  
//        }
//      }
      
      if(motors[0].check_power() > MIN_MOTOR_POWER)
        motors[0].low_motor_power(STEP);
      if(motors[1].check_power() > MIN_MOTOR_POWER)
        motors[1].low_motor_power(STEP); 
      motors[2].up_motor_power(STEP);
      motors[3].up_motor_power(STEP);  
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '6':
//      if(motors[2].check_power()-STEP <= MIN_MOTOR_POWER || motors[3].check_power()-STEP <= MIN_MOTOR_POWER){
//        if(motors[0].check_power() < motors[1].check_power()){
//          motors[0].up_motor_power(STEP);     
//        }else if(motors[0].check_power() > motors[1].check_power()){
//          motors[1].up_motor_power(STEP);
//        }else{
//          motors[0].up_motor_power(STEP);
//          motors[1].up_motor_power(STEP);
//        }
//      }else{
//        if(motors[2].check_power() < motors[3].check_power()){
//          motors[3].low_motor_power(STEP);          
//        }else if(motors[2].check_power() > motors[3].check_power()){
//          motors[2].low_motor_power(STEP);
//        }else{
//          motors[2].low_motor_power(STEP);
//          motors[3].low_motor_power(STEP);  
//        }
//      }
      if(motors[2].check_power() > MIN_MOTOR_POWER)
        motors[2].low_motor_power(STEP);
      if(motors[3].check_power() > MIN_MOTOR_POWER)
        motors[3].low_motor_power(STEP); 
      motors[0].up_motor_power(STEP);
      motors[1].up_motor_power(STEP);  
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '7':
      for(i = 0; i < 4; i++){
        motors[i].low_motor_power(UP_DOWN_STEP);
      }
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
  }
}

void establishContact() {
  int check;
  while (Serial.available() <= 0) {
    digitalWrite(RED_LED,HIGH);
    delay(300);
    Serial.println("A"); 
    digitalWrite(RED_LED,LOW);
    delay(300);
  }
}
