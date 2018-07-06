#include"reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

u16 time;
u8 i,j;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void display()
{
  LSA=1;
  LSB=1;
  LSC=1;
  P0=smgduan[i];
  i++;
  if(i==9) i=0;
}



void Timer0Init()
{
   TMOD=0x01;
   TH0=0xfc;
   TL0=0x18;
   EA=1;
   ET0=1;
   TR0=1;
}



void main()
{
  
   Timer0Init();
   while(1)
   {
      if(time==1000)
	 {
	  
	 	time=0;
		display();

		    switch(j)
			{
			   case(0):P2=0x7f;break;
			   case(1):P2=0xbf;break;
			   case(2):P2=0xdf;break;
			   case(3):P2=0xef;break;
			   case(4):P2=0xf7;break;
			   case(5):P2=0xfb;break;
			   case(6):P2=0xfd;break;
			   case(7):P2=0xfe;break;
			}
			j++; 			
		    if(j==8) j=0;
	  }
	 }
	
}


void Timer0() interrupt 1
{
	 TH0=0xfc;
     TL0=0x18;
	 time++;
	



}