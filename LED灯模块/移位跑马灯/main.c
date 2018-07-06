#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

#define LED P2

void delay(u16 i)
{
   while(i--);
}

void main(void)
{
   u8 i;
   u8 dat ;
   while(1)
   {
	  dat = 0xfe;
      for(i=0; i<8; i++)
	  {	  
	     LED = dat;
	     dat = (dat<<1)|0x01;
		 delay(10000);
		 if(dat==0x7f) break;
	  }
	  for(i=0; i<8; i++)
	  {
	  	 LED = dat;
		 dat = (dat>>1)|0x80;
		 delay(10000);
		 if(dat==0xfe) break;
	  }
	  for(i=0; i<8;i++)
	  {
	  	 LED = dat;
		 dat=dat<<1;
		 delay(10000);
		 if(dat==0x00) break; 
	  }
	  dat = 0x7f;
      for(i=0;i<8;i++)
      {
		  LED = dat;
		  dat=dat>>1;
		  delay(10000);
      }
	  dat = 0x3f;
	  for(i=0;i<4;i++)
	  {
	  	  LED = dat;
		  dat=(dat>>2)|0xc0;
		  delay(100000);
		  if(dat == 0xfc) break;
	  }
	  for(i=0;i<4;i++)
	  {
	  	  LED = dat;
		  dat = (dat<<2)|0x03;
		  delay(100000);
	  }
   }
}