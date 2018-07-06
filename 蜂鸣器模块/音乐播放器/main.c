

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "SoundPlay.h"
#include"music.h"

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;
sbit k1 = P3^0;
sbit k2 = P3^1;
sbit k3 = P3^2;



void Delay1ms(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<120;j++);
}

u8 key_scan()
{
   		if(k1==0)
		{
		   Delay1ms(10);
		   if(k1==0)
		   {
		   	return 1;
		   }
		}

			if(k2==0)
		{
		   Delay1ms(10);
		   if(k2==0)
		   {
			return 2;
		   }
		}

			if(k3==0)
		{
		   Delay1ms(10);
		   if(k3==0)
		   {
			 return 3;
		   }
		}
	
}
void main()
{
    u8 key;
	InitialSound();
	while(1)
	{
	   key = key_scan();
	   switch(key)
	   {
	       case(1):
		         
				     Play(Music_Girl,0,3,360); break;
				   
		   case(2):
				      Play(Music_Same,0,3,360);break;
				   
		   case(3):
				      Play(Music_Two,0,3,360);break;
				  
	   } 
	}
}