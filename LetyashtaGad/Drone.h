#include "Energia.h"
#include "Motor.h"

#ifndef Drone_h
#define Drone_h
#define FRONT_LEFT_MOTOR this->motors[0]
#define FRONT_RIGHT_MOTOR this->motors[1]
#define BACK_LEFT_MOTOR this->motors[3]
#define BACK_RIGHT_MOTOR this->motors[2]

#define FRONT_LEFT_MOTOR_BINARY 0b0001
#define FRONT_RIGHT_MOTOR_BINARY 0b0010
#define BACK_LEFT_MOTOR_BINARY 0b0100
#define BACK_RIGHT_MOTOR_BINARY 0b1000

#define GO_LEFT_BINARY 0b1010
#define GO_RIGHT_BINARY 0b0101
#define GO_FORWARD_BINARY 0b1100
#define GO_BACKWARD_BINARY 0b0011

enum drone_move{
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD,
    UP,
    DOWN,
    MOTOR_STOP
};

class Drone{
  private:
    Motor motors[4];
    void change_position(char,int);
    int get_opposite_motor(int);
  public:
    Drone();
    void move(drone_move);
    void start();
    void one_motor_test();
};
#endif
