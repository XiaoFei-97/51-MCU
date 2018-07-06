#include"reg51.h"
typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA=P2^2;									  //�˿ڶ���
sbit LSB=P2^3;
sbit LSC=P2^4;

void delay(u16 num)
{
  unsigned x,y;
  for(x=num;x>0;x--)
  for(y=110;y>0;y--);
}


u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ
void DigDisplay()
{
  u8 i;
  for(i=0;i<8;i++)
  {
  switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		P0=smgduan[i];//���Ͷ���
		delay(200); //���һ��ʱ��ɨ��	
		P0=0x00;//����
   }
}
void main()
{
  while(1)
  {
    DigDisplay();
  }
}

