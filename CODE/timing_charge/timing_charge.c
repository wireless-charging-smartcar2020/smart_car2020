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

sbit Rom_CS=P2^5;//CSA,  	//L ��Ч,�ֿ�Ƭѡ
sbit LCD_CS1=P2^6;//CSB,  	//L ��Ч,��Ƭѡ
sbit LCD_RES=P2^7;//RST,  	//L ��Ч,����λ
sbit LCD_RS=P4^1;//A0,  	//L:command; H:data,����/����
sbit LCD_SCL=P1^1;//SCK,ʱ��   &�ֿ�IC��SCK
sbit LCD_SID=P1^2;//MISO,�������� &�ֿ�IC��SI
sbit Rom_OUT=P1^3;//MOSI,�������
sbit BL=P1^4;  	//L ��Ч,�������

sbit buzzer=P2^4;
sbit jidianqi=P2^3;

uchar code bmp1[];
uchar str16x16[32];
uchar str8x16[16];
uchar str5x8[5];

//��ʱ
void delay(int n_ms)
{
int j,k;
for(j=0;j<n_ms;j++)
for(k=0;k<110;k++);
}

//����ʱ
void delay_us(int n_us)
{
int j,k;
for(j=0;j<n_us;j++)
for(k=0;k<1;k++);
}

//дָ�LCD ģ��
void transfer_command_lcd(int data1)
{
char i;
LCD_CS1=0;
LCD_RS=0;
for(i=0;i<8;i++)
{
LCD_SCL=0;
//delay_us(10); //��������ʱ
if(data1&0x80) LCD_SID=1;
else LCD_SID=0;
_nop_();
LCD_SCL=1;
_nop_();
LCD_SCL=0;
//delay_us(10); //��������ʱ
//data1=data1<<=1;
	data1=(data1<<1);
}
LCD_CS1=1;
}

//д���ݵ�LCD ģ��
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
//LCD ģ���ʼ��
void initial_lcd()
{
LCD_RES=0; //�͵�ƽ��λ
delay(100);
LCD_RES=1; //��λ���
delay(100);
transfer_command_lcd(0xE2); //��λ
delay(5);
transfer_command_lcd(0x2C); //��ѹ����1
delay(50);
transfer_command_lcd(0x2E); //��ѹ����2
delay(50);
transfer_command_lcd(0x2F); //��ѹ����3
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
transfer_command_lcd(0xB0+page-1); //����ҳ��ַ��ÿ8 ��Ϊһҳ��ȫ����64 �У����ֳ�8 ҳ
transfer_command_lcd(0x10+(column>>4&0x0F)); //�����е�ַ�ĸ�4 λ
transfer_command_lcd(column&0x0F); //�����е�ַ�ĵ�4 λ
}

//ȫ������
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

//����
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

////��ʾ128x64 ����ͼ��
//void display_128x64(uchar *dp)
//{
//uint i,j;
//for(j=0;j<8;j++)
//{
//lcd_address(j+1,1);
//for (i=0;i<128;i++)
//{
//transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
//dp++;
//}
//}
//}

////��ʾ16x16 ����ͼ�񡢺��֡���Ƨ�ֻ�16x16 ���������ͼ��
//void display_graphic_16x16(uchar page,uchar column,uchar *dp)
//{
//uint i,j;
//for(j=0;j<2;j++)
//{
//lcd_address(page+j,column);
//for (i=0;i<16;i++)
//{
//transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
//dp++;
//}
//}
//}
////��ʾ8x16 ����ͼ��ASCII, ��8x16 ����������ַ�������ͼ��
//void display_graphic_8x16(uchar page,uchar column,uchar *dp)
//{
//uint i,j;
//for(j=0;j<2;j++)
//{
//lcd_address(page+j,column);
//for (i=0;i<8;i++)
//{
//transfer_data_lcd(*dp); //д���ݵ�LCD,ÿд��һ��8 λ�����ݺ��е�ַ�Զ���1
//dp++;
//}
//}
//}


////��ʾ5X8 ����ͼ��ASCII, ��5x8 ����������ַ�������ͼ��
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

//��ָ��ֿ�IC
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

//���ֿ�IC ��ȡ���ֻ��ַ����ݣ�1 ���ֽڣ�
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

//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_16x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS = 0;
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //��ַ�ĸ�8 λ,��24 λ
send_command_to_ROM((fontaddr&0xff00)>>8); //��ַ����8 λ,��24 λ
send_command_to_ROM(fontaddr&0xff); //��ַ�ĵ�8 λ,��24 λ
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
transfer_data_lcd(disp_data); //д���ݵ�LCD,ÿд��1 �ֽڵ����ݺ��е�ַ�Զ���1
}
}
}

//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_8x16(ulong fontaddr,uchar page,uchar column)
{
uchar i,j,disp_data;
Rom_CS = 0;
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //��ַ�ĸ�8 λ,��24 λ
send_command_to_ROM((fontaddr&0xff00)>>8); //��ַ����8 λ,��24 λ
send_command_to_ROM(fontaddr&0xff); //��ַ�ĵ�8 λ,��24 λ
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
transfer_data_lcd(disp_data); //д���ݵ�LCD,ÿд��1 �ֽڵ����ݺ��е�ַ�Զ���1
}
}
}

//��ָ����ַ��������д��Һ����ָ����page,column)������
void get_and_write_5x8(ulong fontaddr,uchar page,uchar column)
{
uchar i,disp_data;
Rom_CS = 0;
send_command_to_ROM(0x03);
send_command_to_ROM((fontaddr&0xff0000)>>16); //��ַ�ĸ�8 λ,��24 λ
send_command_to_ROM((fontaddr&0xff00)>>8); //��ַ����8 λ,��24 λ
send_command_to_ROM(fontaddr&0xff); //��ַ�ĵ�8 λ,��24 λ
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
transfer_data_lcd(disp_data); //д���ݵ�LCD,ÿд��1 �ֽڵ����ݺ��е�ַ�Զ���1
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
//������壨GB2312���������ֿ�IC �еĵ�ַ�����¹�ʽ�����㣺
//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
//���ڵ���8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
fontaddr = (text[i]- 0xb0)*94;
fontaddr += (text[i+1]-0xa1)+846;
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
i+=2;
column+=16;
}
else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
{
//������壨GB2312��15x16 ����ַ����ֿ�IC �еĵ�ַ�����¹�ʽ�����㣺
//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
//���ڵ���8 λ��Ƭ���г˷�������⣬���Է�����ȡ��ַ
fontaddr = (text[i]- 0xa1)*94;
fontaddr += (text[i+1]-0xa1);
fontaddr = (ulong)(fontaddr*32);
get_and_write_16x16(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
i+=2;
column+=16;
}
else if((text[i]>=0x20) &&(text[i]<=0x7e))
{
fontaddr = (text[i]- 0x20);
fontaddr = (unsigned long)(fontaddr*16);
fontaddr = (unsigned long)(fontaddr+0X3CF80);
get_and_write_8x16(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
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
get_and_write_5x8(fontaddr,page,column); //��ָ����ַ��������д��Һ����ָ����page,column)������
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
	
	display_GB2312_string(3,1,"...�����..."); 
	display_GB2312_string(5,1,"���ȣ�"); 
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
				display_GB2312_string(3,1,"������"); 
				display_GB2312_string(5,1,"С��׼������");
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