
#ifndef _PWM_H 
#define _PWM_H 

#include "main.h"

#define FSCLK	11059200 //单片机系统时钟的频率
 // 双电机输出pwm
//sbit Left_A=P2^6;
//sbit Left_B=P2^5;
//sbit Right_A=P4^0;
//sbit Right_B=P4^7;

sbit Left_A=P2^6;
sbit Left_B=P2^5;
sbit Right_A=P2^3;
sbit Right_B=P2^1;

extern uint PERCENT_L,PERCENT_R,pwm_L,pwm_R;     //pwm占空比 0~100
extern uchar timeL,timeR; // 定义占空比的变量

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