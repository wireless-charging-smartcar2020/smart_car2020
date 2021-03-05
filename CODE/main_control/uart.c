#include "uart.h"
//#include "adc.h"
#include "pwm.h"
#include "sensor.h"
uchar tmp;

//定义端口
sbit led0=P2^0;		    //指示灯0
sbit led1=P2^1;			//指示灯1

////声明函数
//void InitUART();               //串口初始化
//void SendOneByte(uchar c);	   //单字节发送函数
//void UARTInterrupt();          //串口中断函数

////主函数
//void main(void)
//{
//    InitUART();
//}

//串口初始化函数
void InitUART()
{
    TMOD = 0x20;    // 定时器1工作于方式2
    SCON = 0x50;    //串口工作模式1

    TH1 = 0xFD;     // 波特率9600
    TL1 = TH1;
    PCON = 0x00;

    EA = 1;
    ES = 1;
    TR1 = 1;
}

//单字节数据发送函数
void SendOneByte(uchar c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

//串口中断函数
void UARTInterrupt()    interrupt 4
{

    if(RI)  //确认接收数据
    {
        RI = 0;
        tmp=SBUF;

        //选择函数
        switch(tmp)
        {
				case '2':
  //进入蓝牙模式
				    uart_flag=1;
				P0_sensor=0xff;
            SendOneByte(tmp);
            break;
				
				case '1':
 //进入循迹模式
				    uart_flag=0;
            SendOneByte(tmp);
            break;
					
        case 'f':
            goforward();

            SendOneByte(tmp);
            break;

        case 'b':
            goback();

            SendOneByte(tmp);
            break;
				
				case 'l':
            goLeft();

            SendOneByte(tmp);
            break;
				
				case 'r':
            goRight();

            SendOneByte(tmp);
            break;
				
				case 's':
            gostop();

            SendOneByte(tmp);
            break;

				case 't':
					  SendOneByte(P0_sensor);
				    break;
//        default:                    //其他，灯全灭
//            led0=1;
//            led1=1;
//            SendOneByte(tmp);
        }

    }
    else
        TI = 0;
}
