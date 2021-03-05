/*********************************************************************************************************
** ���̹��� ��PWM���
*********************************************************************************************************/
#include "pwm.h"
#include "sensor.h"
uint PERCENT_L=10,PERCENT_R=10,pwm_L=0,pwm_R=0;     //pwmռ�ձ� 0~100
uchar timeL,timeR; // ����ռ�ձȵı���

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

TR0=0;//����ֵʱ���رն�ʱ��
	TH0 = (65536-FSCLK/12/20000)/256;	 //���ö�ʱ���ĸ�8λ  0.05ms
	TL0 = (65536-FSCLK/12/20000)%256;	 //���ö�ʱ���ĵ�8λ
TR0=1;//�򿪶�ʱ��
	
 

timeL++;
timeR++;

if(timeL>=100) 
{ timeL=0; 
	getsensor(uart_flag);
}
if(timeR>=100) 
	 timeR=0; 
if(timeL<=PERCENT_L) //ռ�ձ�%30,�ɸ�
	pwm_L=1;
else if(timeL>PERCENT_L)
	pwm_L=0;
if(timeR<=PERCENT_R) //ռ�ձ�%30,�ɸ�
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
** �������� ����ʼ��Timer0
*********************************************************************************************************/
void Timer0_init()
{
TMOD=0x01;//��ʱ��0������ʽ1					   
	TH0 = (65536-FSCLK/12/20000)/256;	 //���ö�ʱ���ĸ�8λ  0.05ms
	TL0 = (65536-FSCLK/12/20000)%256;	 //���ö�ʱ���ĵ�8λ
EA=1;//�����ж�
 
ET0=1;//����ʱ��0�ж�
 
TR0=1;//������ʱ��0
}