#ifndef Motor_h
#define Motor_h

//////////////////////CONFIGURATION///////////////////////////////
#define MIN_MOTOR_POWER 1000  //set the min(start) motor value
#define MAX_MOTOR_POWER 2000  //set the max motor value
//////////////////////////////////////////////////////////////////

class Motor{
	private:
		int value;
    int ppm_time;
    bool valueToPPMTime();
	public:
		Motor();
		bool setValue(int);
    int getPPMTime();
    int getValue();
};
#endif
