#include<msp430g2553.h>


class Motor{
  private:
    int id;
    int type;
    int current_power;
    int frequency;
    int max_motor_power;
    int min_motor_power;
    int up_down_step;
    int off_power;
    void change_power(int next_power){
      analogWrite1(this->id,next_power,this->frequency);
    }
    void set_motor_power(int next_power){
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
    
  public:
    Motor(int id, int type){
      this->id = id;
      this->type = type;
      switch(type){
        case 1:
          this->frequency = 50;
          this->current_power = 1;
          this->max_motor_power = 25;
          this->min_motor_power = 12;
          this->up_down_step = 1;
          this->off_power = 10;
          break;
        case 2:
          this->frequency = 500;
          this->current_power = 125;
          this->max_motor_power = 200;
          this->min_motor_power = 150;
          this->up_down_step = 5;
          this->off_power = 125;
          break;
      }
    }
    void up_motor_power(){
      int next_power = (this->current_power + this->up_down_step);
      if(next_power > this->min_motor_power){
        this->set_motor_power(next_power);
      }else{
        this->set_motor_power(this->min_motor_power);
      }
    }
    void low_motor_power(){
      int next_power = (this->current_power - this->up_down_step);
      if(next_power > this->min_motor_power){
        this->set_motor_power(next_power);
      }else{
        this->set_motor_power(this->min_motor_power);
      }
    }
    void init_motor(){
     // if(this->type == 1){
        this->set_motor_power(this->max_motor_power);
      //}else if(this->type == 2){
        //this->set_motor_power(this->off_power);        
      //}
    }
    void ready_motor(){
      this->set_motor_power(this->off_power);
    }
    void stop_motor(){
       this->set_motor_power(this->off_power);
    }
    void max_low(){
       this->set_motor_power(1);
    }
    
    
    
 
    int check_power(){
      return  this->current_power;
    }
    
    int get_id(){
      return  this->id;
    }
};

Motor motor[4] = {{9,2},
                   {14,1},
                   {10,2}, 
                   {19,1}
                  };
                            
int i = 0;
int input = -1;

void establishContact();

void setup() {
  
  
  pinMode(RED_LED, OUTPUT);  
  
  Serial.begin(9600);
  establishContact();
  
  digitalWrite(RED_LED,HIGH);
  
  while(input = Serial.read(),  input != 'R');
  for(i = 0; i < 4; i++){
    pinMode(motor[i].get_id(), OUTPUT); 
    motor[i].init_motor();
  }
  while(input = Serial.read(),  input != 'S');
  for(i = 0; i < 4; i++){
    motor[i].ready_motor();
  }
}

void loop(){
  digitalWrite(RED_LED,LOW);
  input = -1;
  while((input = Serial.read()) <= -1);// 1 - up all motors 2 - low all motors 3 - left 4 -right 5 - forward 6 - back
  Serial.println(input);
  switch(input){
    case '1':
      for(i = 0; i < 4; i++){
        motor[i].up_motor_power();  
      }
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case '2':
      for(i = 0; i < 4  ; i++){
        motor[i].low_motor_power();        
      }
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
     case '7':
       for(i = 0; i < 4; i++){
         motor[i].stop_motor();  
       }
       break;
     case '9':
       for(i = 0; i < 4; i++){
         motor[i].max_low();  
       }
       break;
//    case '3':
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
      
//      if(motors[1].check_power() > MIN_MOTOR_POWER)
//        motors[1].low_motor_power(STEP);
//      if(motors[2].check_power() > MIN_MOTOR_POWER)
//        motors[2].low_motor_power(STEP); 
//      motors[0].up_motor_power(STEP);
//      motors[3].up_motor_power(STEP);  
//      digitalWrite(RED_LED,HIGH);
//      delay(300);
//      break;
//    case '4':
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
//      if(motors[0].check_power() > MIN_MOTOR_POWER)
//        motors[0].low_motor_power(STEP);
//      if(motors[3].check_power() > MIN_MOTOR_POWER)
//        motors[3].low_motor_power(STEP); 
//      motors[1].up_motor_power(STEP);
//      motors[2].up_motor_power(STEP);  
//      digitalWrite(RED_LED,HIGH);
//      delay(300);
//      break;
//    case '5':
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
      
//      if(motors[0].check_power() > MIN_MOTOR_POWER)
//        motors[0].low_motor_power(STEP);
//      if(motors[1].check_power() > MIN_MOTOR_POWER)
//        motors[1].low_motor_power(STEP); 
//      motors[2].up_motor_power(STEP);
//      motors[3].up_motor_power(STEP);  
//      digitalWrite(RED_LED,HIGH);
//      delay(300);
//      break;
//    case '6':
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
//      if(motors[2].check_power() > MIN_MOTOR_POWER)
//        motors[2].low_motor_power(STEP);
//      if(motors[3].check_power() > MIN_MOTOR_POWER)
//        motors[3].low_motor_power(STEP); 
//      motors[0].up_motor_power(STEP);
//      motors[1].up_motor_power(STEP);  
//      digitalWrite(RED_LED,HIGH);
//      delay(300);
//      break;
//    case '7':
//      for(i = 0; i < 4; i++){
//        motors[i].low_motor_power(UP_DOWN_STEP);
//      }
//      digitalWrite(RED_LED,HIGH);
//      delay(300);
//      break;
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
