#include"reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit led=P2^0;


void UsartInit()
{
   TMOD=0x20;    //��ʱ��ѡ��ʽ2
   TH1=0xf3;
   TL1=0xf3;	   //������Ϊ7200bps
   TR1=1;		 //��ʱ��1����
   SCON=0x50;	//���ڿ��ƼĴ���
   PCON=0x80;	  //�����ʷ���
   ES=1;	  //�����ж�����
   EA=1;	  //�ܿ�������
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