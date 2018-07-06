#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit k1 = P3^1;
sbit k2 = P3^0;

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

u8 disp[3];
u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

u8 num;

void delay(u16 i)
{
   while(i--);
}

void keypros()
{
   if(k1 == 0)
   {
   	  delay(1000);
	  if(k1 == 0)
	     {
		 	 num++;
		 }
		 while(!k1);
   }
   if(k2 == 0)
   {
   	   delay(1000);
	   if(k2 == 0)
	   {
	        num = 0;
	   }
	   while(!k2);
   }
}

void datapros()
{
   disp[0] = num%100%10;
   disp[1] = num%100/10;
   disp[2] = num/100;
}

void display()
{
	u8 i;
	for(i=0; i<2; i++)
	{
	   switch(i)
	   {
	   	   case(0):LSA = 0; LSB = 0; LSC = 0;break;
		   case(1):LSA = 1; LSB = 0; LSC = 0;break;
		   case(2):LSA = 0; LSB = 1; LSC = 0;break;
	   }
	   P0 = smgduan[disp[i]];
	   delay(1000);
	   P0 = 0x00;
	}

}

void main()
{
   	while(1)
	{
	   keypros();
	   datapros();
	   display();
	}
}
