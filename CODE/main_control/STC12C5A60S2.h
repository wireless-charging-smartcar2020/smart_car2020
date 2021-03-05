/*--------------------------------------------------------------------------
5204.H

Header file for 8-bit STC microcontrollers.
Copyright (c) 1988-2010 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __5204_H__
#define __5204_H__

/*  BYTE Registers  */
sfr P0    = 0x80;
sfr P1    = 0x90;
sfr P2    = 0xA0;
sfr P3    = 0xB0;
sfr PSW   = 0xD0;
sfr ACC   = 0xE0;
sfr B     = 0xF0;
sfr SP    = 0x81;
sfr DPL   = 0x82;
sfr DPH   = 0x83;
sfr PCON  = 0x87;
sfr TCON  = 0x88;
sfr TMOD  = 0x89;
sfr TL0   = 0x8A;
sfr TL1   = 0x8B;
sfr TH0   = 0x8C;
sfr TH1   = 0x8D;
sfr IE    = 0xA8;
sfr IP    = 0xB8;
sfr SCON  = 0x98;
sfr SBUF  = 0x99;
sfr PLASF = 0x9D;

/*  5204 Extensions  */
sfr CH         = 0XF9;
sfr CCAP0H     = 0XFA;
sfr CCAP1H     = 0XFB;
sfr PCA_PWM0   = 0XF2;
sfr PCA_PWM1   = 0XF3;
sfr CL         = 0XE9;
sfr CCAP0L     = 0XEA;
sfr CCAP1L     = 0XEB;
sfr CCON       = 0XD8;
sfr CMOD       = 0XD9;
sfr CCAPM0     = 0XDA;
sfr CCAPM1     = 0XDB;
sfr P5         = 0XC8;
sfr P5M1       = 0XC9;
sfr P5M0       = 0XCA;
sfr SPSTAT     = 0XCD;
sfr SPCTL      = 0XCE;
sfr SPDAT      = 0XCF;
sfr P4         = 0XC0;
sfr WDT_CONTR  = 0XC1;
sfr IAP_DATA   = 0XC2;
sfr IAP_ADDRH  = 0XC3;
sfr IAP_ADDRL  = 0XC4;
sfr IAP_CMD    = 0XC5;
sfr IAP_TRIG   = 0XC6;
sfr IAP_CONTR  = 0XC7;
sfr P4SW       = 0XBB;
sfr ADC_CONTR  = 0XBC;
sfr ADC_RES    = 0XBD;
sfr ADC_RESL   = 0XBE;
sfr P3M1       = 0XB1;
sfr P3M0       = 0XB2;
sfr P4M1       = 0XB3;
sfr P4M0       = 0XB4;
sfr IP2        = 0XB5;
sfr IP2H       = 0XB6;
sfr IPH        = 0XB7;
sfr IE2        = 0XAF;
sfr BUS_SPEED  = 0XA1;
sfr AUXR1      = 0XA2;
sfr S2CON      = 0X9A;
sfr S2BUF      = 0X9B;
sfr BRT        = 0X9C;
sfr P1ASF      = 0X9D;
sfr P1M1       = 0X91;
sfr P1M0       = 0X92;
sfr P0M1       = 0X93;
sfr P0M0       = 0X94;
sfr P2M1       = 0X95;
sfr P2M0       = 0X96;
sfr CLK_DIV    = 0X97;
sfr AUXR       = 0X8E; 
sfr WAKE_CLK0  = 0X8F;



/*  8052 Extensions  */
sfr T2CON  = 0xC8;
sfr T2MOD  = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;

/*  89E564 Extensions */
sfr IPA   = 0xF8;
sfr IEA   = 0xE8;
sfr SADEN = 0xA9;
sfr SPSR  = 0xAA;


sfr WDTD  = 0x85;
sfr SPDR  = 0x86;
sfr SFCF  = 0xB1;
sfr SFCM  = 0xB2;
sfr SFAL  = 0xB3;
sfr SFAH  = 0xB4;
sfr SFDT  = 0xB5;
sfr SFST  = 0xB6;
sfr SPCR  = 0xD5;
sfr IPAH  = 0xF7;

/*  BIT Registers  */
/*  PSW  */
sbit CY    = PSW^7;
sbit AC    = PSW^6;
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;
sbit P     = PSW^0; //8052 only

/*  TCON  */
sbit TF1   = TCON^7;
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;

/*  IPH  */
/*
sbit PPCAH   = IPH^7;
sbit PLVDH   = IPH^6;
sbit PADCH   = IPH^5;
sbit PSH     = IPH^4;
sbit PT1H    = IPH^3;
sbit PX1H    = IPH^2;
sbit PT0H    = IPH^1;
sbit PX0H    = IPH^0;
*/

/*  IE  */
sbit EA    = IE^7;
sbit ELVD  = IE^6; 
sbit EADC  = IE^5; 
sbit ES    = IE^4;
sbit ET1   = IE^3;
sbit EX1   = IE^2;
sbit ET0   = IE^1;
sbit EX0   = IE^0;

/*  IE2  */
/*
sbit ESPI   = IE2^1;
sbit ES2    = IE2^0;
*/

/*  IP2  */
/*
sbit PSPI   = IP2^1;
sbit PS2    = IP2^0;
*/

/*  IP2H  */
/*
sbit PSPIH   = IP2H^1;
sbit PS2H    = IP2H^0;
*/
/*  IP  */
sbit PPCA   = IP^7;
sbit PLVD   = IP^6;
sbit PADC   = IP^5;
sbit PS     = IP^4;
sbit PT1    = IP^3;
sbit PX1    = IP^2;
sbit PT0    = IP^1;
sbit PX0    = IP^0;

/*  P3  */
sbit RD    = P3^7;
sbit WR    = P3^6;
sbit T1    = P3^5;
sbit T0    = P3^4;
sbit INT1  = P3^3;
sbit INT0  = P3^2;
sbit TXD   = P3^1;
sbit RXD   = P3^0;

/*  SCON  */
sbit SM0   = SCON^7;
sbit SM1   = SCON^6;
sbit SM2   = SCON^5;
sbit REN   = SCON^4;
sbit TB8   = SCON^3;
sbit RB8   = SCON^2;
sbit TI    = SCON^1;
sbit RI    = SCON^0;

/*  P1  */
sbit T2EX  = P1^1; // 8052 only
sbit T2    = P1^0; // 8052 only
             
/*  T2CON  */
sbit TF2    = T2CON^7;
sbit EXF2   = T2CON^6;
sbit RCLK   = T2CON^5;
sbit TCLK   = T2CON^4;
sbit EXEN2  = T2CON^3;
sbit TR2    = T2CON^2;
sbit C_T2   = T2CON^1;
sbit CP_RL2 = T2CON^0;

/*  AUXR  */
 /*
sbit T0X12        = AUXR^7;
sbit T1X12        = AUXR^6;
sbit UART_M0X6    = AUXR^5;
sbit BRTR         = AUXR^4;
sbit S2SMOD       = AUXR^3;
sbit BRTx12       = AUXR^2;
sbit EXTRAM       = AUXR^1;
sbit S1BRS        = AUXR^0;
*/

/*  PCON  */
/*
sbit SMOD          = PCON^7;
sbit SMOD0         = PCON^6;
sbit LVDF          = PCON^5;
sbit POF           = PCON^4;
sbit GF1           = PCON^3;
sbit GF0           = PCON^2;
sbit PD            = PCON^1;
sbit IDL           = PCON^0;
*/


/*  WAKE_CLK0  */
/*
sbit PCAWAKEUP            = WAKE_CLK0^7;
sbit RXD_PIN_IE           = WAKE_CLK0^6;
sbit T1_PIN_IE            = WAKE_CLK0^5;
sbit T0_PIN_IE            = WAKE_CLK0^4;
sbit LVD_WAKE             = WAKE_CLK0^3;
sbit BRTCLK0              = WAKE_CLK0^2;
sbit T1CLK0               = WAKE_CLK0^1;
sbit T0CLK0               = WAKE_CLK0^0;
*/


/*  ADC_CONTR  */
/*
sbit ADC_POWER           = ADC_CONTR^7;
sbit SPEED1              = ADC_CONTR^6;
sbit SPEED0              = ADC_CONTR^5;
sbit ADC_FLAG            = ADC_CONTR^4;
sbit ADC_START           = ADC_CONTR^3;
sbit CHS2                = ADC_CONTR^2;
sbit CHS1                = ADC_CONTR^1;
sbit CHS0                = ADC_CONTR^0;
*/
 
/*  CCON  */
sbit CF                  = CCON^7; 
sbit CR                  = CCON^6; 
sbit CCF1                = CCON^1; 
sbit CCF0                = CCON^0; 

/*  CMOD  */
/*
sbit CIDL                = CMOD^7; 
sbit CPS2                = CMOD^3; 
sbit CPS1                = CMOD^2; 
sbit CPS0                = CMOD^1; 
sbit ECF                 = CMOD^0; 
*/

/*  CCAPM0  */
/*
sbit ECOM0                = CCAPM0^6; 
sbit CAPP0                = CCAPM0^5; 
sbit CAPN0                = CCAPM0^4; 
sbit MAT0                 = CCAPM0^3; 
sbit TOG0                 = CCAPM0^2; 
sbit PWM0                 = CCAPM0^1; 
sbit ECCF0                = CCAPM0^0; 
*/

/*  CCAPM1  */
/*
sbit ECOM1                = CCAPM1^6; 
sbit CAPP1                = CCAPM1^5; 
sbit CAPN1                = CCAPM1^4; 
sbit MAT1                 = CCAPM1^3; 
sbit TOG1                 = CCAPM1^2; 
sbit PWM1                 = CCAPM1^1; 
sbit ECCF1                = CCAPM1^0; 
*/


/*  PCA_PWM0  */
/*
sbit EPC0H                = PCA_PWM0^1; 
sbit EPC0L                = PCA_PWM0^0; 
*/


/*  PCA_PWM1  */
/*
sbit EPC1H                = PCA_PWM1^1; 
sbit EPC1L                = PCA_PWM1^0; 
*/

/*  P1ASF  */
/*
sbit P17ASF                = P1ASF^7; 
sbit P16ASF                = P1ASF^6; 
sbit P15ASF                = P1ASF^5; 
sbit P14ASF                = P1ASF^4; 
sbit P13ASF                = P1ASF^3; 
sbit P12ASF                = P1ASF^2; 
sbit P11ASF                = P1ASF^1; 
sbit P10ASF                = P1ASF^0; 
*/


/*  CLK_DIV */
/*
sbit CLKS2                = CLK_DIV^2; 
sbit CLKS1                = CLK_DIV^1; 
sbit CLKS0                = CLK_DIV^0; 
*/


/*  AUXR1 */
/*
sbit PCA_P4                = AUXR1^6; 
sbit SPI_P4                = AUXR1^5; 
sbit S2_P4                 = AUXR1^4; 
sbit GF2                   = AUXR1^3; 
sbit ADRJ                  = AUXR1^2; 
sbit DPS                   = AUXR1^0; 
*/


/*  BUS_SPEED */
/*
sbit ALES1                 = BUS_SPEED^5; 
sbit ALES0                 = BUS_SPEED^4;  
sbit RWS2                  = BUS_SPEED^2;  
sbit RWS1                  = BUS_SPEED^1;  
sbit RWS0                  = BUS_SPEED^0;   
*/

/*  P4SW  */
/*
sbit LVD_P4.6 = P4SW^6;
sbit ALE_P4.5 = P4SW^5;
sbit NA_P4.4  = P4SW^4;
*/



/*  TMOD */
/*
sbit GATE      = TMOD^7;
sbit GATE1     = TMOD^7;
sbit C/T#      = TMOD^6;
sbit C/T#1     = TMOD^6;
sbit M1        = TMOD^5;
sbit M1_1      = TMOD^5;
sbit M0        = TMOD^4;
sbit M0_0      = TMOD^4;
sbit GATE      = TMOD^3;
sbit GATE0     = TMOD^3;
sbit C/T#      = TMOD^2;
sbit C/T0#     = TMOD^2;
sbit M1        = TMOD^1;
sbit M0_1      = TMOD^1;
sbit M0        = TMOD^0;
sbit M0_0      = TMOD^0;
*/

/*  S2CON */
/*
sbit S2SM0      = S2CON^7;
sbit S2SM1      = S2CON^6;
sbit S2SM2      = S2CON^5;
sbit S2REN      = S2CON^4;
sbit S2TB8      = S2CON^3;
sbit S2RB8      = S2CON^2;
sbit S2TI       = S2CON^1;
sbit S2RI       = S2CON^0;
*/


/* IAP_CMD */
/*
sbit MS1       = IAP_CMD^1;
sbit MS0       = IAP_CMD^0;
*/

/* IAP_CONTR */
/*
sbit IAPEN       = IAP_CONTR^7;
sbit SWBS        = IAP_CONTR^6;
sbit SWRST       = IAP_CONTR^5;
sbit CMD_FAIL    = IAP_CONTR^4;
sbit WT2         = IAP_CONTR^2;
sbit WT1         = IAP_CONTR^1;
sbit WT0         = IAP_CONTR^0;
*/


/* ADC_RES */
/*
sbit ADC_RES9       = ADC_RES^1;
sbit ADC_RES8       = ADC_RES^0;
*/

/* ADC_RESL */
/*
sbit ADC_RES7       = ADC_RESL^7;
sbit ADC_RES6       = ADC_RESL^6;
sbit ADC_RES5       = ADC_RESL^5;
sbit ADC_RES4       = ADC_RESL^4;
sbit ADC_RES3       = ADC_RESL^3;
sbit ADC_RES2       = ADC_RESL^2;
sbit ADC_RES1       = ADC_RESL^1;
sbit ADC_RES0       = ADC_RESL^0;
*/

/* SPCTL */
/*
sbit SSIG       = SPCTL^7;
sbit SPEN       = SPCTL^6;
sbit DORD       = SPCTL^5;
sbit WSTR       = SPCTL^4;
sbit CPOL       = SPCTL^3;
sbit CPHA       = SPCTL^2;
sbit SPR1       = SPCTL^1;
sbit SPR0       = SPCTL^0;
*/

/* SPSTAT */
/*
sbit SPIF       = SPSTAT^7;
sbit WCOL       = SPSTAT^6;
*/
#endif
