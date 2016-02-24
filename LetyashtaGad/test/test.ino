void setup() {
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  Serial.begin(9600);
  establishContact();
  delay(1000);
  digitalWrite(8,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void establishContact() {
  while (Serial.available() <= 0) {
    digitalWrite(8,HIGH);
    delay(300);
    Serial.print(1);   // send a capital A
    digitalWrite(8,LOW);
    delay(300);
  }
}
