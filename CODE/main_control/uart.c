#include "uart.h"
//#include "adc.h"
#include "pwm.h"
#include "sensor.h"
uchar tmp;

//����˿�
sbit led0=P2^0;		    //ָʾ��0
sbit led1=P2^1;			//ָʾ��1

////��������
//void InitUART();               //���ڳ�ʼ��
//void SendOneByte(uchar c);	   //���ֽڷ��ͺ���
//void UARTInterrupt();          //�����жϺ���

////������
//void main(void)
//{
//    InitUART();
//}

//���ڳ�ʼ������
void InitUART()
{
    TMOD = 0x20;    // ��ʱ��1�����ڷ�ʽ2
    SCON = 0x50;    //���ڹ���ģʽ1

    TH1 = 0xFD;     // ������9600
    TL1 = TH1;
    PCON = 0x00;

    EA = 1;
    ES = 1;
    TR1 = 1;
}

//���ֽ����ݷ��ͺ���
void SendOneByte(uchar c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

//�����жϺ���
void UARTInterrupt()    interrupt 4
{

    if(RI)  //ȷ�Ͻ�������
    {
        RI = 0;
        tmp=SBUF;

        //ѡ����
        switch(tmp)
        {
				case '2':
  //��������ģʽ
				    uart_flag=1;
				P0_sensor=0xff;
            SendOneByte(tmp);
            break;
				
				case '1':
 //����ѭ��ģʽ
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
//        default:                    //��������ȫ��
//            led0=1;
//            led1=1;
//            SendOneByte(tmp);
        }

    }
    else
        TI = 0;
}
