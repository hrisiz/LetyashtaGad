#define STEP 5
#define START_POWER 125
class Motor{
  private:
    int id;
    int current_power;
    
  public:
    Motor(int id, int power){
      this->id = id;
      this->current_power = power; 
    }
    
    void up_motor_power(int up_with){
      int next_power = this->current_power + up_with;
      if(next_power > 255){
         next_power = 255; 
      }
      for(int counter = this->current_power; counter < next_power; counter++){
        analogWrite( this->id, counter );
      }
      analogWrite( this->id, next_power );
      this->current_power = next_power;   
    }
    
    void low_motor_power(int low_with){
      int next_power = this->current_power - low_with;
      if(next_power < START_POWER){
         next_power = START_POWER; 
      }
      for(int counter = this->current_power; counter > next_power; counter--){
        analogWrite( this->id, counter );
      }
      analogWrite( this->id, next_power );
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

int up_drone();
int down_drone();

int turn_left();
int turn_right();
int go_forward();
int go_back();

void establishContact();

void setup() {
  for(i = 0; i < 4; i++){
    pinMode(motors[i].get_id(), OUTPUT); 
    analogWrite(motors[i].get_id(),START_POWER);
  }
  
  pinMode(RED_LED, OUTPUT);  
  
  Serial.begin(9600);
  establishContact();
  
  digitalWrite(RED_LED,HIGH);
  
  while(input = Serial.read(),  input != 1);
}

void loop(){
  digitalWrite(RED_LED,LOW);
  input = -1;
  while(input = Serial.read(),  input < 1 && input > 6); // 1 - up all motors 2 - low all motors 3 - left 4 -right 5 - forward 6 - back
  
  switch(input){
    case 1:
      up_drone();
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
    case 2:
      down_drone();
      digitalWrite(RED_LED,HIGH);
      delay(300);
      break;
//    case 3:
//      turn_left();
//      break;
//    case 4:
//      turn_right();
//      break;
//    case 5:
//      go_forward();
//      break;
//    case 6:
//      go_back();
//      break;
  }
}

int up_drone(){
  for(i = 0; i < 4; i++){
    motors[i].up_motor_power(STEP);
  }
}

int down_drone(){
  for(i = 0; i < 4; i++){
    motors[i].low_motor_power(STEP);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    digitalWrite(RED_LED,HIGH);
    delay(300);
    Serial.write(1); // send a capital A
    digitalWrite(RED_LED,LOW);
    delay(300);
  }
}
