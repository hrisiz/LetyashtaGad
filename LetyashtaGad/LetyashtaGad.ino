#define STEP 5
#define START_POWER 125

typedef struct Motor{
  const int id;
  int current_power;
} motor;

motor motors[4] = {14,13,12,10};

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
    pinMode(motors[i].id, OUTPUT); 
    analogWrite(motors[i].id,START_POWER);
  }
  
  pinMode(RED_LED, OUTPUT);  
  
  Serial.begin(9600);
  establishContact();
  
  digitalWrite(RED_LED,HIGH);
  
  while(input = Serial.read(),  input != 0);
}

void loop(){
  digitalWrite(RED_LED,LOW);
  input = -1;
  while(input = Serial.read(),  input < 1 && input > 6); // 1 - up all motors 2 - low all motors 3 - left 4 -right 5 - forward 6 - back
  switch(input)({
    case 1:
      up_drone();
      break;
    case 2:
      down_drone();
      break;
    case 3:
      turn_left();
      break;
    case 4:
      turn_right();
      break;
    case 5:
      go_forward();
      break;
    case 6:
      go_back():
      break;
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
