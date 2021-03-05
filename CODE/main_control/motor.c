/*********************************************************************************************************
** 工程功能 ：motor姿态控制、pid运算
*********************************************************************************************************/
#include "motor.h"
extern uint pwm_L,pwm_R;
void move(uchar mode)   //F,B,L,R 前后左右
{
	switch(mode)
	{
		case 'F':
			Left_A=pwm_L;
			Left_B=0;
			Right_A=pwm_R;
			Right_B=0;
			break;
		case 'B':
			Left_A=0;
			Left_B=pwm_L;
			Right_A=0;
			Right_B=pwm_R;
			break;
		case 'L':
			Left_A=pwm_L;
			Left_B=0;
			Right_A=0;
			Right_B=pwm_R;
			break;
		case 'R':
			Left_A=0;
			Left_B=pwm_L;
			Right_A=pwm_R;
			Right_B=0;
			break;
		default:
			printf("move error!");
			break;
	}
//	Delay_ms(time);
}


