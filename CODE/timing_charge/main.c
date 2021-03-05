#include "main.h"
#define CHARGE_TIME 10
uchar second=CHARGE_TIME;
	void main()        
{ 
//CSA=0;  	//L 有效,字库片选
//CSB=0;  	//L 有效,屏片选
//RST=0;  	//L 有效,屏复位 
//A0=0;  	//L:command; H:data,命令/数据 
//SCK =0;//时钟  	
//SI=0;//数据输入 
//SO =0;//数据输出 
//BL=0;  	//L 有效,背光控制 
//	//buzzer=1;
//	jidianqi=0;
//	TMOD=0x01;
//	TH0=(65536-46080)/256;
//	TL0=(65536-46080)%256;
//	EA=1;
//	ET0=1;
//	TR0=1;
//	while(1)  
//		{  
//		//led1=0;
//			if(second==0)     // 60  
//			{
//			  second=0; 
//        A1=0;A2=0;				
//				//buzzer=0;
//				delay(50000);
//				jidianqi=1;
//				display(A1,A2);
//			}
//			A1=second/10;     
//			A2=second%10;  
//			//display(A1,A2);	
//		}  
} 
/*
50ms*20=1s
0.05/(12/11059200)=46080
*/
void T0_time() interrupt 1
{
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	num++;
	if(num==20)
	{
		num=0;
		if(second>0)
		    second--;      
	}
}



//..........串口写.......... 
void serial_write(uchar lcm_cmd_or_data) 
{ 
 	uchar i;  	
	CSB=0;  	
	for(i=0;i<8;i++) 
 	{
 	SCK=0;   
 	 	if((lcm_cmd_or_data&0x80)==0x80)  	 	
		  SI=1;  	
		else  	 	
		  SI=0;  	
		//SCK=0;  
		_nop_();  
		_nop_();  	
		SCK=1;
		_nop_();
		SCK=0; 	
		lcm_cmd_or_data=lcm_cmd_or_data<<1; 
} 
 	CSB=1; 
} 
//..........写命令.......... 
void send_cmd(uchar lcm_cmd) 
{ 
 	A0=0; 
 	serial_write(lcm_cmd); 
} 
//..........写数据到 DDRAM.......... 
void send_data(uchar lcm_data) 
{ 
 	A0=1; 
 	serial_write(lcm_data); 
} 
//==================display a piture of 16*16 dots================
void display_graphic_16x16(char page,char column,char *dp)
{
	char i,j;
	for(j=0;j<2;j++)
	{
		//lcd_address(page+j,column);
 	 	set_page_address(page+j);  	 	
		set_column_address(column); 
		for (i=0;i<16;i++)
		{	
			send_data(*dp);		
			dp++;
		}
	}
}
//..........写页地址.......... 
void set_page_address(uchar page_addr) 
{ 
 	send_cmd(page_addr|0xb0); 
} 
//..........写列地址.......... 
void set_column_address(uchar clm_addr) 
{ 
 	send_cmd((clm_addr>>4)|0x10);  	//送列地址高四位 
 	send_cmd(clm_addr&0x0f);  	//送列地址低四位 
} 
//..........初始化.......... 
void lcm_init(void) 
{ 
 	delay(3);  
   	RST=0;  	
	delay(3);  	
	RST=1;  	
	delay(6); 
	send_cmd(0xAE);
	send_cmd(0xE2);//Software reset
	send_cmd(0xa0); //0xA0左右镜像选择，0xA1正常显示 	
	send_cmd(0xc8); //0xC0上下镜像选择，0xC8正常显示
	send_cmd(0x25);//set (Rb/Ra) 
	send_cmd(0xa2);//bias set:1/9 
	send_cmd(0x81);//vo output voltage set 
	send_cmd(0x10);   //0~63
	send_cmd(0xf8),//booster ratio set
	send_cmd(0x00),//booster ratio:4x
	send_cmd(0x2c);//升压步聚1 
	send_cmd(0x2e);//升压步聚2 
	send_cmd(0x2f);//升压步聚3
	send_cmd(0x40); //起始行：第一行开始 
//	send_cmd(0xe0);  	

	send_cmd(0xaf);//开显示
} 
//..........延时 n 毫秒.......... 
void delay(uint ms) 
{ 
 	uint i,j;  	
	for(i=0;i<ms;i++)  	 	
	for(j=0;j<20000;j++); 
} 
void display(uchar sh_c,uchar g_c)      
{  
	lcm_init(); 
	BL = 0;
	while(1) 
{  	
delay(01); 
		display_graphic_16x16(1,8,huan);
delay(01); 
		display_graphic_16x16(1,(8+16),ying);
delay(01); 
		display_graphic_16x16(1,(8+16*2),ni);
delay(05);        //waitkey();
}
//***************数码管显示*******************//
//	//dula=0; 
//	dula=1;   
//	P0=table[sh_c];   	
//	dula=0;  
//	P0=0xff;
//	
//	wela=1;
//	P0=0xfe;  
//	wela=0;  
//	delay(500);       // 5ms  
//	
//	dula=1;	
//	P0=table[g_c];      
//	dula=0; 	
//	P0=0xff;
//	
//	wela=1;  
//	P0=0xfd;  
//	wela=0;  
//	delay(500);       // 5ms  
//****************数码管************************//
}  