#include"reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit led=P2^0;


void UsartInit()
{
   TMOD=0x20;    //定时器选择方式2
   TH1=0xf3;
   TL1=0xf3;	   //波特率为7200bps
   TR1=1;		 //定时器1启动
   SCON=0x50;	//串口控制寄存器
   PCON=0x80;	  //波特率翻倍
   ES=1;	  //串口中断允许
   EA=1;	  //总开关允许
}

void main()
{ 
   UsartInit();
   while(1);
}

void Usart() interrupt 4
{
	u8 recieveData;
	recieveData=SBUF;
	RI=0;
	SBUF=recieveData;
		if(recieveData==1) led=0;
	while(!TI);

	TI=0;
}