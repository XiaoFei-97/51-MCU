#include"reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;
sbit led1=P2^7;
sbit led2=P2^5;
sbit led3=P2^3;
sbit led4=P2^1; 



void delay(u16 i)
{
   while(i--);
}

void keypros()
{
   if(k1==0)
   {
   	  delay(1000);
	  if(k1==0)
	  {
	  	 led1=~led1;
	  }
	  while(!k1);
   }
	  if(k2==0)
   {
   	  delay(1000);
	  if(k2==0)
	  {
	  	 led2=~led2;
	  }
	  while(!k2);
   }
   if(k3==0)
   {
   	  delay(1000);
	  if(k3==0)
	  {
	  	 led3=~led3;
	  }
	  while(!k3);
   }
   if(k4==0)
   {
   	  delay(1000);
	  if(k4==0)
	  {
	  	 led4=~led4;
	  }
	  while(!k4);
   }
}


void main()
{
   while(1)
   {
   keypros();
	}
}