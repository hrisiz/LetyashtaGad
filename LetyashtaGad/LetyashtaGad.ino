#define STEP 10
#define START_POWER 100
const int hight_motor_power = 8; 
const int low_motor_power = 5;
const int motor_pin =  14;
int button[2];
int i = 0;
int state = START_POWER;

int motor_power(int motor_pin,int motor_state,int power);
void setup() {
  pinMode(motor_pin, OUTPUT);  
  pinMode(hight_motor_power, INPUT_PULLUP);  
  pinMode(low_motor_power, INPUT_PULLUP);   
  analogWrite(motor_pin,state);
  while(digitalRead(hight_motor_power));
  delay(100);
}

void loop(){
  delay(200);
  while(button[1] = digitalRead(low_motor_power),button[2] = digitalRead(hight_motor_power),button[1] == HIGH && button[2] == HIGH);
  if(!button[1]){
    if(state-STEP < START_POWER){
      state = START_POWER; 
    }else{
      state = motor_power(motor_pin,state,state-STEP);
    }
  }
  if(!button[2]){
    if(state+STEP > 200){
      state = 200; 
    }else{ 
      state = motor_power(motor_pin,state,state+STEP);
    }
  }
}

int motor_power(int motor_pin,int motor_state,int power){
  int i;
  if(power < motor_state){
    for(i = motor_state; i > power; i--){
      analogWrite(motor_pin,i); 
    } 
  }else{
    for(i = motor_state; i < power; i++){
      analogWrite(motor_pin,i); 
    }
  } 
  return i;
}
