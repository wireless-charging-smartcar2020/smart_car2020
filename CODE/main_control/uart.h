#ifndef _UART_H 
#define _UART_H


#include "main.h"
//��������
void InitUART();               //���ڳ�ʼ��
void SendOneByte(uchar c);	   //���ֽڷ��ͺ���
void UARTInterrupt();          //�����жϺ���

#endif
