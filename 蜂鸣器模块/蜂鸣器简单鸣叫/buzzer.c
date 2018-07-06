#include"reg52.h"
typedef unsigned char u8;
typedef unsigned int u16;
sbit beep=P1^5;

void delay(u16 num)
{
  u16 x,y;
  for(x=num;x>0;x--)
  for(y=110;y>0;y--);
}

void main()
{
  while(1)
  {
  	beep=~beep;
	delay(100);
  }
}