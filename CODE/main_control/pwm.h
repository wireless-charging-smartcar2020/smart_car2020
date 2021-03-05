
#ifndef _PWM_H 
#define _PWM_H 

#include "main.h"

#define FSCLK	11059200 //��Ƭ��ϵͳʱ�ӵ�Ƶ��
 // ˫������pwm
//sbit Left_A=P2^6;
//sbit Left_B=P2^5;
//sbit Right_A=P4^0;
//sbit Right_B=P4^7;

sbit Left_A=P2^6;
sbit Left_B=P2^5;
sbit Right_A=P2^3;
sbit Right_B=P2^1;

extern uint PERCENT_L,PERCENT_R,pwm_L,pwm_R;     //pwmռ�ձ� 0~100
extern uchar timeL,timeR; // ����ռ�ձȵı���

enum list{forward,back,Left,Right,stop};
extern enum list action;

void goforward();

void goback();

void goLeft();

void goRight();

void gostop();
void Timer0_init();

void tim0();
//void tim0() interrupt 1; //????

#endif