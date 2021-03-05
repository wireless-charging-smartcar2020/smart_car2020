#ifndef _PID_H 
#define _PID_H

#include "main.h"

struct pid_typedef
{
	float kp;
	float ki;
	float kd;
	float dx;
	float sum_dx;
	float previous_dx;
	float pre_previous_dx;
	float f_dx;
};

extern struct pid_typedef pid1,pid2;

void pid_init(void);
void pid_deinit(struct pid_typedef *pid);
float pid_position_type(struct pid_typedef *pid,float desired,float actual);//位置式pid
float pid_increment_type(struct pid_typedef *pid,float desired,float actual);//增量式pid

#endif
