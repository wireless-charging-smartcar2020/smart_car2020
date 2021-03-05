#include "sensor.h"
#include "pwm.h"
int uart_flag=0,transform=0;
uchar i=0,j=0,k,P0_sensor;
/*
void goforward();

void goback();

void goLeft();

void goRight();

void gostop();
*/
void getsensor(int uart_flag)
{
	if(!uart_flag)
	{
		P0_sensor=(P0|0xe0); //ÆÁ±Î¸ßÈýÎ»
		switch(P0_sensor)
		{
			case 0xf7: i=1;goLeft();break;
			case 0xef: i=2;goLeft();break;
			case 0xe7: i=3;goLeft();break;
			case 0xe3: i=4;goLeft();break;
			case 0xf3: i=5;goLeft();break;
			
			case 0xfe: j=1;goRight();break;
			case 0xfc: j=2;goRight();break;
			case 0xf8: j=3;goRight();break;
			case 0xf9: j=4;goRight();break;
			case 0xfd: j=5;goRight();break;
			
			case 0xfb: k=1;goforward();break;
			case 0xf1: k=2;goforward();break;
			
			case 0xe0:     gostop();break;
			
			case 0xff: 
				if(i==1||i==2||i==3||i==4||i==5)
			   {
					 i=0;goLeft();				 
			   }
				 	if(j==1||j==2||j==3||j==4||j==5)
			   {
					 j=0;goRight();				 
			   }
				 	if(k==1||k==2)
			   {
					 k=0;goforward();		 
			   }
				 break;
			default :break;
		}
	}
}