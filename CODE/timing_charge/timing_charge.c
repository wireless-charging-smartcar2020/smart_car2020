#include <reg52.h>
#include <intrins.h>

#include <ctype.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define CHARGE_TIME 6
uchar second=CHARGE_TIME;
uint num=0;
int persent=0;

sbit Rom_CS=P2^5;//CSA,  	//L 有效,字库片选
sbit LCD_CS1=P2^6;//CSB,  	//L 有效,屏片选
sbit LCD_RES=P2^7;//RST,  	//L 有效,屏复位
sbit LCD_RS=P4^1;//A0,  	//L:command; H:data,命令/数据
sbit LCD_SCL=P1^1;//SCK,时钟   &字库IC的SCK
sbit LCD_SID=P1^2;//MISO,数据输入 &字库IC的SI
sbit Rom_OUT=P1^3;//MOSI,数据输出
sbit BL=P1^4;  	//L 有效,背光控制

sbit buzzer=P2^4;
sbit jidianqi=P2^3;

uchar code bmp1[];
uchar str16x16[32];
uchar str8x16[16];
uchar str5x8[5];

//延时
void delay(int n_ms)
{
int j,k;
for(j=0;j<n_ms;j++)
for(k=0;k<110;k++);
}

//短延时
void delay_us(int n_us)
{
int j,k;
for(j=0;j<n_us;j++)
for(k=0;k<1;k++);
}

//写指令到LCD 模块
void transfer_command_lcd(int data1)
{
char i;
LCD_CS1=0;
LCD_RS=0;
for(i=0;i<8;i++)
{
LCD_SCL=0;
//delay_us(10); //加少量延时
if(data1&0x80) LCD_SID=1;
else LCD_SID=0;
_nop_();
LCD_SCL=1;
_nop_();
LCD_SCL=0;
//delay_us(10); //加少量延时
//data1=data1<<=1;
	data1=(data1<<1);
}
LCD_CS1=1;
}

//写数据到LCD 模块
void transfer_data_lcd(int data1)
{
char i;

LCD_CS1=0;
LCD_RS=1;
for(i=0;i<8;i++)
{
LCD_SCL=0;
if(data1&0x80) LCD_SID=1;
else LCD_SID=0;
_nop_();
LCD_SCL=1;
_nop_();
LCD_SCL=0;
//data1=data1<<=1;
	data1=(data1<<1);
}
LCD_CS1=1;
}
//LCD 模块初始化
void initial_lcd()
{
LCD_RES=0; //低电平复位
delay(100);
LCD_RES=1; //复位完毕
delay(100);
transfer_command_lcd(0xE2); //软复位
delay(5);
transfer_command_lcd(0x2C); //升压步聚1
delay(50);
transfer_command_lcd(0x2E); //升压步聚2
delay(50);
transfer_command_lcd(0x2F); //升压步聚3
delay(5);

transfer_command_lcd(0xA2);//bias set:1/9
transfer_command_lcd(0xA0);//ADC select:nomal);0->128
transfer_command_lcd(0xC8);//commom output mode select: reverse
transfer_command_lcd(0xA6);//normal/reverse  display
transfer_command_lcd(0xF8);//booster ratio set
transfer_command_lcd(0x00);//booster ratio:4x
transfer_command_lcd(0x2F);//power control set
transfer_command_lcd(0x26);//set (Rb/Ra)
transfer_command_lcd(0x81);//vo output voltage set
transfer_command_lcd(0x08);//voltage volume =9.0v
//0x40);//set start line
transfer_command_lcd(0xAF);//display on
}

void lcd_address(uint page,uint column)
{
column=column-0x01;
transfer_command_lcd(0xB0+page-1); //设置页地址，每8 行为一页，全屏共64 行，被分成8 页
transfer_command_lcd(0x10+(column>>4&0x0F)); //设置列地址的高4 位
transfer_command_lcd(column&0x0F); //设置列地址的低4 位
}

//全屏清屏
void clear_screen()
{
unsigned char i,j;
for(i=0;i<9;i++)
{
transfer_command_lcd(0xB0+i);
transfer_command_lcd(0x10);
transfer_command_lcd(0x00);
for(j=0;j<132;j++)
{
transfer_data_lcd(0x00);
}
}
}

//满屏
void fill_screen()
{
unsigned char i,j;
for(i=0;i<9;i++)
{
transfer_command_lcd(0xB0+i);
transfer_command_lcd(0x10);
transfer_command_lcd(0x00);
for(j=0;j<132;j++)
{
transfer_data_lcd(0xFF);
}
}
}

////显示128x64 点阵图像
//void display_128x64(uchar *dp)
//{
//uint i,j;
//for(j=0;j<8;j++)
//{
//lcd_address(j+1,1);
//for (i=0;i<128;i++)
//{
//transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
//dp++;
//}
//}
//}

////显示16x16 点阵图像、汉字、生僻字或16x16 点阵的其他图标
//void display_graphic_16x16(uchar page,uchar column,uchar *dp)
//{
//uint i,j;
//for(j=0;j<2;j++)
//{
//lcd_address(page+j,column);
//for (i=0;i<16;i++)
//{
//transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
//dp++;
//}
//}
//}
////显示8x16 点阵图像、ASCII, 或8x16 点阵的自造字符、其他图标
//void display_graphic_8x16(uchar page,uchar column,uchar *dp)
//{
//uint i,j;
//for(j=0;j<2;j++)
//{
//lcd_address(page+j,column);
//for (i=0;i<8;i++)
//{
//transfer_data_lcd(*dp); //写数据到LCD,每写完一个8 位的数据后列地址自动加1
//dp++;
//}
//}
//}


////显示5X8 点阵图像、ASCII, 或5x8 点阵的自造字符、其他图标
//void display_graphic_5x8(uchar page,uchar column,uchar *dp)
//{
//uint i;
//lcd_address(page,column);
//for (i=0;i<6;i++)
//{
//transfer_data_lcd(*dp);
//dp++;
//}
//}

//送指令到字库IC
void send_command_to_ROM( uchar datu )
{
uchar i;
for(i=0;i<8;i++ )
{
LCD_SCL=0;
delay_us(10);
if(datu&0x80)LCD_SID = 1;
else LCD_SID = 0;
datu = datu<<1;
LCD_SCL=1;
delay_us(10);
}
}

//从字库IC 中取汉字或字符数据（1 个字节）
static uchar get_data_from_ROM( )
{
uchar i;
uchar ret_data=0;
for(i=0;i<8;i++)
{
//Rom_OUT=1;
LCD_SCL=0;
//delay_us(10);
ret_data=ret_data<<1;
if( Rom_OUT )
ret_data=ret_data+1;
else
ret_data=ret_data+0;
LCD_SCL=1;
//delay_us(10);
}
Rom_OUT=0;
return(ret_data);
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS = 0;
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //地址的高8 位,共24 位
send_command_to_ROM((fontaddr&0xff00)>>8); //地址的中8 位,共24 位
send_command_to_ROM(fontaddr&0xff); //地址的低8 位,共24 位
for(i=0; i<32; i++ )
{
disp_data=get_data_from_ROM();
str16x16[i]=disp_data;
}
Rom_CS=1;
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for(i=0; i<16; i++ )
{
disp_data=str16x16[16*j+i];
transfer_data_lcd(disp_data); //写数据到LCD,每写完1 字节的数据后列地址自动加1
}
}
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS = 0;
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //地址的高8 位,共24 位
send_command_to_ROM((fontaddr&0xff00)>>8); //地址的中8 位,共24 位
send_command_to_ROM(fontaddr&0xff); //地址的低8 位,共24 位
for(i=0; i<16; i++ )
{
disp_data=get_data_from_ROM();
str8x16[i]=disp_data;
}
Rom_CS=1;
for(j=0;j<2;j++)
{
lcd_address(page+j,column);
for(i=0; i<8; i++ )
{
disp_data=str8x16[8*j+i];
transfer_data_lcd(disp_data); //写数据到LCD,每写完1 字节的数据后列地址自动加1
}
}
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column)
{
uchar i,disp_data;
Rom_CS = 0;
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //地址的高8 位,共24 位
send_command_to_ROM((fontaddr&0xff00)>>8); //地址的中8 位,共24 位
send_command_to_ROM(fontaddr&0xff); //地址的低8 位,共24 位
for(i=0; i<5; i++ )
{
disp_data=get_data_from_ROM();
str5x8[i]=disp_data;
}
Rom_CS=1;
lcd_address(page,column);
for(i=0; i<5; i++ )
{
disp_data=str5x8[i];
transfer_data_lcd(disp_data); //写数据到LCD,每写完1 字节的数据后列地址自动加1
}
}

//---------------------
ulong fontaddr=0;
void display_GB2312_string(uchar page,uchar column,uchar *text)
{
uchar i= 0;
while((text[i]>0x00))
{
if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
{
//国标简体（GB2312）汉字在字库IC 中的地址由以下公式来计算：
//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
//由于担心8 位单片机有乘法溢出问题，所以分三部取地址
fontaddr = (text[i]- 0xb0)*94;
fontaddr += (text[i+1]-0xa1)+846;
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=2;
column+=16;
}
else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
{
//国标简体（GB2312）15x16 点的字符在字库IC 中的地址由以下公式来计算：
//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
//由于担心8 位单片机有乘法溢出问题，所以分三部取地址
fontaddr = (text[i]- 0xa1)*94;
fontaddr += (text[i+1]-0xa1);
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=2;
column+=16;
}
else if((text[i]>=0x20) &&(text[i]<=0x7e))
{
fontaddr = (text[i]- 0x20);
fontaddr = (unsigned long)(fontaddr*16);
fontaddr = (unsigned long)(fontaddr+0X3CF80);
get_and_write_8x16(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=1;
column+=8;
}
else
i++;
}
}

void display_string_5x8(uchar page,uchar column,uchar *text)
{
unsigned char i= 0;
while((text[i]>0x00))
{
if((text[i]>=0x20) &&(text[i]<=0x7E))
{
fontaddr = (text[i]- 0x20);
fontaddr = (unsigned long)(fontaddr*8);
fontaddr = (unsigned long)(fontaddr+0x3bfc0);
get_and_write_5x8(fontaddr,page,column); //从指定地址读出数据写到液晶屏指定（page,column)座标中
i+=1;
column+=6;
}
else
i++;
}
}

//===============main program===================

char str[3];

void main(void)
{
	TMOD=0x01;
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	EA=1;
	ET0=1;
	TR0=1;
	
	BL = 0;
	initial_lcd();
	clear_screen();
	
	display_GB2312_string(3,1,"...充电中..."); 
	display_GB2312_string(5,1,"进度："); 
while(second>0)
{

			persent=100-(float)second/CHARGE_TIME*100;
     str[0]=(persent/10)+'0';
     str[1]=(persent%10)+'0';
		 str[2]='%';
        display_GB2312_string(7,1,str); 
			delay(1000);
			jidianqi=0;
}
			if(second==0)     // 60  
			{
			  second=0; 
				clear_screen();
				display_GB2312_string(3,1,"充电完成"); 
				display_GB2312_string(5,1,"小车准备启动");
				delay(1000);
				buzzer=0;
				delay(1000);
				jidianqi=1;
				delay(1000);
				buzzer=1;
				clear_screen();
				BL = 1;
			while(1);
		  }
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