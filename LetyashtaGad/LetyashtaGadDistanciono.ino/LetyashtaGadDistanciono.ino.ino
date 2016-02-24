#define CHECK_LIGHT 8
int inByte = 0; 
int up = 2;  
int down = 4; 
int start = 7; 
int button[3];
void setup() {
  pinMode(CHECK_LIGHT,OUTPUT);
  digitalWrite(CHECK_LIGHT,LOW);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);
  Serial.begin(9600); 
  //while(digitalRead(start) == HIGH);
  //establishContact();
}

void loop() {
  delay(200);
  digitalWrite(CHECK_LIGHT,LOW);
  while(button[0] = digitalRead(start),button[1] = digitalRead(up),button[2] = digitalRead(down),button[0] == HIGH && button[1] == HIGH && button[2] == HIGH);
  if(button[0] == LOW){
    if (Serial.available() > 0) {
      Serial.write(0);
      digitalWrite(CHECK_LIGHT,HIGH);
    }
  }
  if(button[1] == LOW){
    if (Serial.available() > 0) {
      Serial.write(1);
      digitalWrite(CHECK_LIGHT,HIGH);
    }
  }
  if(button[2] == LOW){
    if (Serial.available() > 0) {
      Serial.write(2);
      digitalWrite(CHECK_LIGHT,HIGH);
    }
  }
}
void establishContact() {
  while (Serial.available() <= 0) {
    digitalWrite(CHECK_LIGHT,HIGH);
    delay(300);
    Serial.write(1);   // send a capital A
    digitalWrite(CHECK_LIGHT,LOW);
    delay(300);
  }
}
