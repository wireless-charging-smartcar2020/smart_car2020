#ifndef _SENSOR_H 
#define _SENSOR_H


#include "main.h"
sbit OUT1=P0^0;
sbit OUT2=P0^1;
sbit OUT3=P0^2;
sbit OUT4=P0^3;
sbit OUT5=P0^4;

extern int uart_flag,transform;
extern uchar i,j,k,P0_sensor;
void getsensor(int uart_flag);
#endif