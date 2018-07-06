#include"reg52.h"
typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delay(u16 i)
{
   while(i--);
}

#define GPIO_KEY P1
#define GPIO_DIG P0

u8 keyvalue;
u8 a;

void keydown()
{
  GPIO_KEY=0x0f;
  if(GPIO_KEY!=0x0f)
  {
  	 delay(1000);
	 if(GPIO_KEY!=0)
	 {
	   GPIO_KEY=0x0f;
	   switch(GPIO_KEY)
	   {
	   	 case(0x07):keyvalue=0;break;
		 case(0x0b):keyvalue=1;break;
		 case(0x0d):keyvalue=2;break;
		 case(0x0e):keyvalue=3;break;
	   }
	     GPIO_KEY=0xf0;
		 switch(GPIO_KEY)
	   {
	   	 case(0x70):keyvalue=keyvalue;break;
		 case(0xb0):keyvalue=keyvalue+4;break;
		 case(0xd0):keyvalue=keyvalue+8;break;
		 case(0xe0):keyvalue=keyvalue+12;break;
	   }
	   while(a<50&&(GPIO_KEY!=0xf0))
	   {
	   	  delay(1000);
		  a++;
	   }

	 }
  }
}
void main()
{
 LSA=0;
 LSB=0;
 LSC=0;
 while(1)
 {
 	keydown();
	GPIO_DIG=smgduan[keyvalue];
 }
}
