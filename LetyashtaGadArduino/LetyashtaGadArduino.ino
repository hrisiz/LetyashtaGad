
//////////////////////CONFIGURATION///////////////////////////////
#define CHANEL_NUMBER 4  //set the number of chanels
#define PPM_FR_LEN 20000  //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PULSE_LEN 300  //set the pulse length
#define ON_STATE 1  //set polarity of the pulses: 1 is positive, 0 is negative
#define SIGNAL_PIN 4  //set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////

#include "Quadcopter.h"

Quadcopter quadcopter = Quadcopter();

//ISR(TIMER2_OVF_vect);

ISR(TIMER1_COMPA_vect);

#define MPU9250_ADDRESS 0x68  // Device address when ADO = 0
#define WHO_AM_I_MPU9250   0x3D // Should return 0x71
void setup()
{ 
  Wire.begin();
  Serial.begin(9600);
  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, !ON_STATE);  //set the PPM signal pin to the default state (off)
  if(quadcopter.getReady()){
    Serial.println("Quadcopter is ready!");
  }
}

void loop()
{
  quadcopter.setDronePos(1.1,1.2,1.4);
}
//
//ISR(TIMER2_OVF_vect) {
//  // second timer code
//  TCNT2 = 5;           //Reset Timer to 130 out of 255
//  TIFR2 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
//}
//

ISR(TIMER1_COMPA_vect) { //leave this alone
  static boolean state = true;

  TCNT1 = 0;

  if (state) { //start pulse
    digitalWrite(SIGNAL_PIN, ON_STATE);
    OCR1A = PPM_PULSE_LEN * 2;
    state = false;
  } else { //end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    digitalWrite(SIGNAL_PIN, !ON_STATE);
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





