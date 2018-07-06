#include<reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;
sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;
sbit led5=P2^4;
sbit led6=P2^5;
sbit led7=P2^6;
sbit led8=P2^7;
void delay(u16 num)
{
   u16 x,y;
   for(x=num;x>0;x--)
   for(y=110;y>0;y--);
}
void main(void)
{
	while(1)
	{
	   led8=0;
	   delay(500);
	   led8=1;
	   delay(500);
	   led7=0;
	   delay(500);
	   led7=1;
	   delay(500);
	   led6=0;
	   delay(500);
	   led6=1;
	   delay(500);
	   led5=0;
	   delay(500);
	   led5=1;
	   delay(500);
	   led4=0;
	   delay(500);
	   led4=1;
	   delay(500);
	   led3=0;
	   delay(500);
	   led3=1;
	   delay(500);
	   led2=0;
	   delay(500);
	   led2=1;
	   delay(500);
	   led1=0;
	   delay(500);
	   led1=1;
	   delay(500);
	}
}

