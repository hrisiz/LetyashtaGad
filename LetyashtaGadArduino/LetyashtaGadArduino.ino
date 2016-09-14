//////////////////////CONFIGURATION///////////////////////////////
#define CHANEL_NUMBER 4  //set the number of chanels
#define PPM_FR_LEN 20000  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PULSE_LEN 300  //set the pulse length
#define ON_STATE 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define SINGAL_PIN 4  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////

#include "Quadcopter.h"
Quadcopter quadcopter = Quadcopter();

ISR(TIMER2_OVF_vect);

ISR(TIMER1_COMPA_vect);

void setup()
{
  pinMode(SINGAL_PIN, OUTPUT);
  digitalWrite(SINGAL_PIN, !ON_STATE);  //set the PPM signal pin to the default state (off)

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register, change this
  OCR1B = 100;  // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
  
  //Setup Timer2 to fire every 16ms
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 5;           //Reset Timer Count to 5 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x07;        //Timer2 Control Reg B: Timer Prescaler set to 1024
  
}

void loop()
{
  
}

ISR(TIMER2_OVF_vect) {
  // second timer code
  TCNT2 = 5;           //Reset Timer to 130 out of 255
  TIFR2 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
}; 

ISR(TIMER1_COMPA_vect) { //leave this alone
  static boolean state = true;

  TCNT1 = 0;

  if (state) { //start pulse
    digitalWrite(SINGAL_PIN, ON_STATE);
    OCR1A = PPM_PULSE_LEN * 2;
    state = false;
  } else { //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    digitalWrite(SINGAL_PIN, !ON_STATE);
    state = true;

    if (cur_chan_numb >= CHANEL_NUMBER) {
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PULSE_LEN;
      OCR1A = (PPM_FR_LEN - calc_rest) * 2;
      calc_rest = 0;
    }
    else {
      int motor_time = quadcopter.getMotor(cur_chan_numb).getPPMTime();
      OCR1A = (motor_time - PPM_PULSE_LEN) * 2;
      calc_rest = calc_rest + motor_time;
      cur_chan_numb++;
    }
  }
}



