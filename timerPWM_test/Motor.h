#ifndef Motor_h
#define Motor_h

class Motor{
	private:
		int id;
    int motor_stat_state;
    int motor_max_state;
		int value;
    int ppm_time;
    void valueToPPMTime();
    void valueToPPMTime(int);
	public:
		Motor(int,int);
		void setValue(int);
    void upValueWith(int);
    int getPPMTime();
    int getValue();
};
#endif
