#ifndef _UART_H 
#define _UART_H


#include "main.h"
//声明函数
void InitUART();               //串口初始化
void SendOneByte(uchar c);	   //单字节发送函数
void UARTInterrupt();          //串口中断函数

#endif
