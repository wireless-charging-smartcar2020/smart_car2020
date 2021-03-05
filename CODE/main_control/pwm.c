/*********************************************************************************************************
** 工程功能 ：PWM输出
*********************************************************************************************************/
#include "pwm.h"
#include "sensor.h"
uint PERCENT_L=10,PERCENT_R=10,pwm_L=0,pwm_R=0;     //pwm占空比 0~100
uchar timeL,timeR; // 定义占空比的变量

enum list action;

void goforward()
{action=forward;}

void goback()
{action=back;}

void goLeft()
{action=Left;}

void goRight()
{action=Right;}

void gostop()
{action=stop;}

void tim0() interrupt 1
{

TR0=0;//赋初值时，关闭定时器
	TH0 = (65536-FSCLK/12/20000)/256;	 //配置定时器的高8位  0.05ms
	TL0 = (65536-FSCLK/12/20000)%256;	 //配置定时器的低8位
TR0=1;//打开定时器
	
 

timeL++;
timeR++;

if(timeL>=100) 
{ timeL=0; 
	getsensor(uart_flag);
}
if(timeR>=100) 
	 timeR=0; 
if(timeL<=PERCENT_L) //占空比%30,可改
	pwm_L=1;
else if(timeL>PERCENT_L)
	pwm_L=0;
if(timeR<=PERCENT_R) //占空比%30,可改
	pwm_R=1;
else if(timeR>PERCENT_R)
	pwm_R=0;

	switch(action)
	{
		case forward:
			Left_A=pwm_L;
			Left_B=0;
			Right_A=pwm_R;
			Right_B=0;
			break;
		case back:
			Left_A=0;
			Left_B=pwm_L;
			Right_A=0;
			Right_B=pwm_R;
			break;
		case Left:
			Left_A=pwm_L;
			Left_B=0;
			Right_A=0;
			Right_B=pwm_R;
			break;
		case Right:
			Left_A=0;
			Left_B=pwm_L;
			Right_A=pwm_R;
			Right_B=0;
			break;
		case stop:
			Left_A=0;
			Left_B=0;
			Right_A=0;
			Right_B=0;
			break;
	}
}
 

/*********************************************************************************************************
** 函数功能 ：初始化Timer0
*********************************************************************************************************/
void Timer0_init()
{
TMOD=0x01;//定时器0工作方式1					   
	TH0 = (65536-FSCLK/12/20000)/256;	 //配置定时器的高8位  0.05ms
	TL0 = (65536-FSCLK/12/20000)%256;	 //配置定时器的低8位
EA=1;//开总中断
 
ET0=1;//开定时器0中断
 
TR0=1;//启动定时器0
}