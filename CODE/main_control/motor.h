#ifndef _MOTOR_H 
#define _MOTOR_H

#include "main.h"

// Ë«µç»úÊä³öpwm
sbit Left_A=P2^5;
sbit Left_B=P2^6;
sbit Right_A=P4^7;
sbit Right_B=P4^1;

void move(uchar mode);

#endif