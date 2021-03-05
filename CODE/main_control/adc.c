/*********************************************************************************************************
** ���̹��� ��adc�ɼ�
*********************************************************************************************************/
#include "adc.h"
#include "pwm.h"
float X1=0,X2=0,X3=0;  //  R M L
	
void get_sensor_value()
{
	ADC_Init(ADC_PORT0 | ADC_PORT1 | ADC_PORT4); //����ͨ��P1^0 ,P1^1,P1^4 ΪAD�ɼ��ڣ���Ҫ�������������ڣ�ֱ���û�����ӽ���ʼ��������
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
void reaction()  //ֵ���޸�
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
	P1ASF=port;//����ADת��ͨ��
	ADC_RES=0;//���ת�����
	ADC_CONTR=ADC_POWER | ADC_SPEEDLL_540;//��ADת������Դ
//	IE=0XA0;//�������жϣ�ADC�ж�
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}

float GetADCResult(unsigned char channel)//��ȡͨ��ch�ĵ�ѹֵ
{
	unsigned int ADC_RESULT = 0;//������Ž��
	float result;
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL_540 | ADC_START | channel;//��ʼת���������ò���ͨ��ΪP1^0
	_nop_();//�辭���ĸ�CPUʱ����ʱ������ֵ���ܱ�֤�����ADC_CONTR���ƼĴ���
	_nop_();
	_nop_();
	_nop_();
	while(!(ADC_CONTR & ADC_FLAG));//�ȴ�ת������
	ADC_CONTR &= ~ADC_FLAG;//�������жϿ���λ
	ADC_RESULT = ADC_RES;
	ADC_RESULT = (ADC_RESULT << 2) | (0x02 & ADC_RESL);	//Ĭ�����ݴ洢��ʽ���߰�λ��ADC_RES,�Ͷ�λ��ADC_RESL�Ͷ�λ
	
	result = ADC_RESULT * 5.0 ;
	//result = ADC_RESULT * 5.0 / 1024.0 ;  //��׼��ѹΪ��Դ��ѹ5V��10�ķֱ��ʣ���1024
	//*1024??
	return result;
}