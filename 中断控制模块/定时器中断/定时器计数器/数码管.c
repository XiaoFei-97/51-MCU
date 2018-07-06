#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u16 time;
u8  num=0,disp[4];
		 

u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f};

void Timer0Init()
{
  TMOD=0x01;
  TH0=0xfc;
  TL0=0x18;
  EA=1;
  ET0=1;
  TR0=1;
}

void delay(u16 i)
{
  while(i--);
}

void datapros()
{
   disp[0]=smgduan[num/1000];
   disp[1]=smgduan[num%1000/100];
   disp[2]=smgduan[num%1000%100/10];
   disp[3]=smgduan[num%1000%100%10];

}

void display()
{
  u8 i;
  for(i=0;i<4;i++)
  {
  switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0;break; //显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0;break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0;break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0;break;//显示第3位	
		}
		P0=disp[3-i];
		delay(100); //间隔一段时间扫描	
		P0=0x00;
   }
}

void main()
{
  	 Timer0Init();
   
     while(1)
	 {
	    datapros();
	 display();
	 }
  
}


void Timer0() interrupt 1
{
    TH0=0xfc;
    TL0=0x18;
	time++;
	 if(time==1000)
	  {
	  	 time=0;
		 num++;
		 if(num>9999) num=0;
         
	  }
}


