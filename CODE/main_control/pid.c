#include "pid.h"


struct pid_typedef pid1,pid2;

float pid_position_type(struct pid_typedef *pid,float desired,float actual)//pid参数，期望值，实际值
{
	pid->dx = desired - actual;
	pid->f_dx = pid->dx*pid->kp + pid->sum_dx*pid->ki + (pid->dx-pid->previous_dx)*pid->kd;
	pid->sum_dx += pid->dx;
	pid->previous_dx = pid->dx;
//			if(pid->sum_dx>3000)pid->sum_dx=3000;
//			if(pid->sum_dx<-3000)pid->sum_dx=-3000;
	return pid->f_dx;
}
float pid_increment_type(struct pid_typedef *pid,float desired,float actual)//pid参数，期望值，实际值
{
	pid->dx = desired - actual;
	pid->f_dx = (pid->dx-pid->previous_dx)*pid->kp + pid->dx*pid->ki 
							+ (pid->dx-2*pid->previous_dx+pid->pre_previous_dx)*pid->kd;
	pid->pre_previous_dx = pid->previous_dx;
	pid->previous_dx = pid->dx;

	return pid->f_dx;
}
void pid_deinit(struct pid_typedef *pid)
{
	pid->sum_dx=0;
	pid->previous_dx=0;
	pid->pre_previous_dx=0;
}
void pid_init()
{
	pid1.kp=0.1;
	pid1.ki=0.05;
	pid1.kd=0;
	pid1.sum_dx=0;
	pid1.previous_dx=0;
	pid1.pre_previous_dx=0;
	
	pid2.kp=1;
	pid2.ki=0.5;
	pid2.kd=1;
	pid2.sum_dx=0;
	pid2.previous_dx=0;
	pid2.pre_previous_dx=0;
}

