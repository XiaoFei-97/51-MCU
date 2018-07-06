#include"reg51.h"
#include"intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit SER=P3^4;
sbit RCLK=P3^5;
sbit SRCLK=P3^6;

void delay(u16 i)
{
    while(i--);
}

u8 ledduan[]={0x61,0x91,0x49,0x25,0x25,0x49,0x91,0x61};
u8 ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void hc595sendbyte(u8 dat)
{
   u8 a;
   SRCLK=0;
   RCLK=0;
   for(a=0;a<8;a++)
   {
	  SER=dat>>7;
	  dat<<=1;
	  SRCLK=1;
	  _nop_();
	  _nop_();
	  SRCLK=0;
   }
   RCLK=1;
   _nop_();
   _nop_();
   RCLK=0;
}

void main()
{
  u8 i;
  while(1)
  {
  	for(i=0;i<8;i++)
	{
	  		P0=ledwei[i];
			hc595sendbyte(ledduan[i]);
			delay(100);
			hc595sendbyte(0x00);
	}
  }
}