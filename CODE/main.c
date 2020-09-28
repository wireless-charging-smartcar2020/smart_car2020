#include <reg52.h>
sbit led1=P1^0;
#define uchar unsigned char
uchar j,k,i,a,A1,A2,second=10;
int num=0;
sbit dula=P2^0;
sbit wela=P2^1;
sbit buzzer=P2^6;
sbit jidianqi=P2^2;
uchar code table[]= 
{
  0x3f,0x06,0x5b,0x4f,0x66,
	0x6d,0x7d,0x07,0x7f,0x6f 
};      //,0x77,0x7c,0x39,0x5e,0x79,0x71
void delay(uchar i)        
{  
	for(j=i;j>0;j--)  
		for(k=125;k>0;k--);  
}  
void display(uchar sh_c,uchar g_c)      
{  
	//dula=0; 
	dula=1;   
	P0=table[sh_c];   	
	dula=0;  
	P0=0xff;
	
	wela=1;
	P0=0xfe;  
	wela=0;  
	delay(500);       // 5ms  
	
	dula=1;	
	P0=table[g_c];      
	dula=0; 	
	P0=0xff;
	
	wela=1;  
	P0=0xfd;  
	wela=0;  
	delay(500);       // 5ms  
}  
	void main()        
{ 
	buzzer=0;
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)  
		{  
			led1=0;
			if(second==0)     // 60  
			{
			  second=0; 
       A1=0;A2=0;				
				buzzer=1;
				jidianqi=0;
			}
			
			A1=second/10;     
			A2=second%10;  
			display(A1,A2);	
		}  
} 
void T0_time() interrupt 1
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	num++;
	if(num==20)
	{
		num=0;
		if(second>0)
		    second--;      
	}
}