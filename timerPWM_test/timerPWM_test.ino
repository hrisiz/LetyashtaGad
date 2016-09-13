/*
 *  Timer1 library example
 *  June 2008 | jesse dot tane at gmail dot com
 */


//////////////////////CONFIGURATION///////////////////////////////
#define chanel_number 4  //set the number of chanels
#define min_motor_power 1000  //set the min(start) motor value
#define max_motor_power 2000  //set the max motor value
#define PPM_FrLen 20000  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300  //set the pulse length
#define onState 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define sigPin 4  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////

#include "Motor.h"


char read_char;
char read_string[20];
int string_len = 0;
Motor motor[4] = {Motor(min_motor_power,max_motor_power),Motor(min_motor_power,max_motor_power),Motor(min_motor_power,max_motor_power),Motor(min_motor_power,max_motor_power)};


void setup()
{
  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, !onState);  //set the PPM signal pin to the default state (off)
  
  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;
  
  OCR1A = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
  Serial.begin(9600);
//  while (!Serial.available()) {
//    Serial.println('A');
//  }
//  Serial.println("Ready!");
  delay(5000);
  for(int i = 0; i < 4; i++){
    motor[i].setValue(max_motor_power-min_motor_power);
  }
  delay(1000);
  for(int i = 0; i < 4; i++){
    motor[i].setValue(0);
  }
//  delay(5000);
//  for(int i = 0; i < 4; i++){
//    motor[i].setValue(800);
//  }
}

void loop()
{
// // put main code here
//  static int val = 1;
//  
//  motor[0].setValue(motor[0].getValue() + val);
//  if(motor[0].getPPMTime() >= 1600){ val = -1; }
//  if(motor[0].getPPMTime() <= 1000){ val = 1; }
//  while((read_char = Serial.read()) == -1);
//  Serial.println(motor[0].getPPMTime());
  next:
  while((read_char = Serial.read()) == -1);   // input type 0 100;2 50;3 80;
  //Serial.println(read_char);
  if(read_char == ';' && string_len > 2){
    int value = 0;
    for(int i = 2; i < string_len; i++){
      if(read_string[i] >= '0' && read_string[i] <= '9'){
        value = (value*10)+(read_string[i] - '0');
      }
    }
    
    if(read_string[2] == '!'){
      Serial.print(motor[read_string[0]-'0'].getValue());
      Serial.println("!");
    }else if(read_string[2] == '+'){
      motor[read_string[0]-'0'].upValueWith(value);
    }else if(read_string[2] == '-'){
      motor[read_string[0]-'0'].upValueWith(value*(-1));
    }else{
      motor[read_string[0]-'0'].setValue(value); 
    }
    
    string_len = 0;
    goto next;
  }else{
    if((read_char >= '0' && read_char <= '9') || (read_char == ' ' && string_len > 0) || ((read_char == '+' || read_char == '!' || read_char == '-') && (string_len > 0 && read_string[string_len-1] == ' '))){
      read_string[string_len] = read_char;
      string_len++;
    }
  }
}

  
ISR(TIMER1_COMPA_vect){  //leave this alone
  static boolean state = true;
  
  TCNT1 = 0;
  
  if(state){  //start pulse
    digitalWrite(sigPin, onState);
    OCR1A = PPM_PulseLen * 2;
    state = false;
  }else{  //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;
  
    digitalWrite(sigPin, !onState);
    state = true;
  
    if(cur_chan_numb >= chanel_number){
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PulseLen;// 
      OCR1A = (PPM_FrLen - calc_rest) * 2;
      calc_rest = 0;
    }
    else{
      OCR1A = (motor[cur_chan_numb].getPPMTime() - PPM_PulseLen) * 2;
      calc_rest = calc_rest + motor[cur_chan_numb].getPPMTime();
      cur_chan_numb++;
    }
  }
}

