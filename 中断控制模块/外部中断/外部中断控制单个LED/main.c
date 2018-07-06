#include"reg51.h" 

typedef unsigned char u8;
typedef unsigned int u16;

sbit led=P2^7;
sbit k4=P3^3;
void delay(u16 i)
{
  while(i--);
}

void Int1Init()			   //中断响应条件
{
   IT1=1;
   EX1=1;
   EA=1;
}

void main()
{
   Int1Init();
   while(1);
}

void Int1() interrupt 2		  //中断函数
{
	delay(1000);
	if(k4==0)
	{
	   led=~led;
	}
}	