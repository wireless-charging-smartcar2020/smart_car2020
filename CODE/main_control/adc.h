#ifndef _ADC_H 
#define _ADC_H

#include "main.h"
#include<intrins.h>
extern float X1,X2,X3;  //红外对管模拟量
/********************************用于配置P1口对应管脚为AD模拟输入口**************************************/
#define ADC_PORT0			0X01
#define	ADC_PORT1			0X02
#define ADC_PORT2			0X04
#define ADC_PORT3			0X08
#define ADC_PORT4			0X10
#define ADC_PORT5			0X20
#define ADC_PORT6			0X40
#define ADC_PORT7			0X80
#define ADC_PORTALL			0XFF

/*************************************用于获取对应通道的电压值******************************************/
#define ADC_CH0				0X00
#define ADC_CH1				0X01
#define ADC_CH2				0X02
#define ADC_CH3				0X03
#define ADC_CH4				0X04
#define ADC_CH5				0X05
#define ADC_CH6				0X06
#define ADC_CH7				0X07

/*********************************************定义AD转换速度*********************************************/
#define ADC_SPEEDLL_540 	0X00           
#define ADC_SPEEDLL_360		0X20
#define ADC_SPEEDLL_180		0X40
#define ADC_SPEEDLL_90		0X60

/***************************************定义转换控制寄存器控制位*****************************************/
#define ADC_POWER   		0X80            //电源控制位
#define ADC_FLAG    		0X10            //转换结束标志位
#define ADC_START   		0X08            //转换开始位



/*********************************************************************************************************
** 函数功能 ：内置ADC的初始化配置
** 函数说明 ：使用内置ADC时需要先配置对应的P1口的管脚为模拟输入
** 入口参数 ：port：需要配置为模拟输入的通道，使用或运算可以同时配置多个管脚
**			  如：ADC_Init(ADC_PORT0 | ADC_PORT1 | ADC_PORT2)调用此函数后可以同时配置P1^0,P1^1,P1^2为模拟输入
** 出口参数 ：无
*********************************************************************************************************/
void ADC_Init(unsigned char port);
/*********************************************************************************************************
** 函数功能 ：获取ADC对应通道的电压值
** 函数说明 ：每次只能获取一个通道的电压值，不同通道需要分别调用该函数获取
** 入口参数 ：channel：获取该通道的电压值
** 出口参数 ：result： 当前通道的电压值
*********************************************************************************************************/
float GetADCResult(unsigned char channel);//读取通道ch的电压值

//巡线函数
void get_sensor_value();
void reaction();
#endif