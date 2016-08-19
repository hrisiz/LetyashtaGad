#include "Energia.h"

#ifndef Motor_h
#define Motor_h

class Motor{
  private:
    int id;
    int type;
    int current_power;
    int frequency;
    int max_motor_power;
    int min_motor_power;
    int up_down_step;
    int off_power;
    int binary;
    void change_power(int);
    void set_motor_power(int);
  public:
    Motor(int id, int type, int binary);
    void up_motor_power();
    void low_motor_power();
    void init_motor();
    void motor_start_power();
    
    boolean is_max();

    int check_power();
    int get_id();
};
#endif
