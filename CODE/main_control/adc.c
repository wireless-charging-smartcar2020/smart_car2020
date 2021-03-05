/*********************************************************************************************************
** 工程功能 ：adc采集
*********************************************************************************************************/
#include "adc.h"
#include "pwm.h"
float X1=0,X2=0,X3=0;  //  R M L
	
void get_sensor_value()
{
	ADC_Init(ADC_PORT0 | ADC_PORT1 | ADC_PORT4); //配置通道P1^0 ,P1^1,P1^4 为AD采集口，如要配置其他其他口，直接用或运算加进初始化函数中
		X1=GetADCResult(ADC_CH0);	
	
		X2=GetADCResult(ADC_CH1);	
		
    X3=GetADCResult(ADC_CH4);
		Delay_ms(1000);	
	printf("ADC TEST:%f,%f,%f", X1,X2,X3);
}

/*
void goforward();

void goback();

void goLeft();

void goRight();

void gostop();
*/
void reaction()  //值待修改
{
	if(X2>450)
	{
		PERCENT_L=30,PERCENT_R=30;
		goforward();
	}
	else if(X3>350)
	{
		PERCENT_L=30,PERCENT_R=30;
		goLeft();
		while(X3>350);
	}
	else if(X1>400)
	{
		PERCENT_L=30,PERCENT_R=30;
		goRight();
		while(X1>400);
	}
}

/************************** (C) COPYRIGHT 2011 Blue Sky Teams *****END OF FILE*****************************/
void ADC_Init(unsigned char port)
{
	P1ASF=port;//设置AD转换通道
	ADC_RES=0;//清空转换结果
	ADC_CONTR=ADC_POWER | ADC_SPEEDLL_540;//打开AD转化器电源
//	IE=0XA0;//开启总中断，ADC中断
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

float GetADCResult(unsigned char channel)//读取通道ch的电压值
{
	unsigned int ADC_RESULT = 0;//用来存放结果
	float result;
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL_540 | ADC_START | channel;//开始转换，并设置测量通道为P1^0
	_nop_();//需经过四个CPU时钟延时，上述值才能保证被设进ADC_CONTR控制寄存器
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR & ADC_FLAG));//等待转换结束
	ADC_CONTR &= ~ADC_FLAG;//软件清除中断控制位
	ADC_RESULT = ADC_RES;
	ADC_RESULT = (ADC_RESULT << 2) | (0x02 & ADC_RESL);	//默认数据存储方式：高八位在ADC_RES,低二位在ADC_RESL低二位
	
	result = ADC_RESULT * 5.0 ;
	//result = ADC_RESULT * 5.0 / 1024.0 ;  //基准电压为电源电压5V，10的分辨率，即1024
	//*1024??
	return result;
}