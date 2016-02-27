#define CHECK_LIGHT 8
#define BUTTONS_COUNT 6

class Button{
  private:
    int id;
    int current_value;
  public:
    Button(int id){
      this->id = id;
    }
    void initialize(){
      pinMode(this->id,INPUT_PULLUP);
    }
    int get_id(){
      return this->id;
    }
    int get_value(){
      return this->current_value;
    }
    void reset_value(){
      this->current_value = LOW;
    }
    int check_for_push(){
      this->current_value = digitalRead(id);
      return this->current_value;
    }
};

Button button[BUTTONS_COUNT] = {2,4,7,8,12,13};
int i = 0;

void setup() {
  pinMode(CHECK_LIGHT,OUTPUT);
  for(int counter=0; counter < BUTTONS_COUNT; counter++){
    button[counter].initialize();
  }
  digitalWrite(CHECK_LIGHT,LOW);
  Serial.begin(9600); 
  establishContact();
}

void loop() {
  digitalWrite(CHECK_LIGHT,LOW);
  if(button[i].check_for_push() != HIGH){
    if (Serial.available() > 0) {
      Serial.write(i+1);
      digitalWrite(CHECK_LIGHT,HIGH);
      delay(200);
    }
  }
  button[i].reset_value();
  if(++i >= BUTTONS_COUNT){
    i = 0;
  }
}
void establishContact() {
  int check;
  while (Serial.available() <= 0 && check != 5) {
    check = Serial.write("hello");
    delay(300);
  }
}
