#include"reg52.h"
typedef unsigned char u8;
typedef unsigned int u16;

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

void Display()
{
   u8 i;
   for(i=0;i<8;i++)
   {
   	  switch(i)
	  {
	  	 case(0):led8=0;delay(500);led8=1;break;
		 case(1):led7=0;delay(500);led7=1;break;
		 case(2):led6=0;delay(500);led6=1;break;
		 case(3):led5=0;delay(500);led5=1;break;
		 case(4):led4=0;delay(500);led4=1;break;
		 case(5):led3=0;delay(500);led3=1;break;
		 case(6):led2=0;delay(500);led2=1;break;
		 case(7):led1=0;delay(500);led1=1;break;
	  }
   }
} 
void main()
{
  while(1)
  {
	  P2=0xff;
  	Display();
  }
}