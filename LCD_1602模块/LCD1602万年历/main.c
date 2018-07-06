
#include"lcd.h"
#include"temp.h"
#include"DS1302.h"

void Timer0Init()
{
    TMOD |= 0X01;	//��ʱ��0������ʽ1
	TH0 = 0XFC;		//��ʱ1us
	TL0 = 0X18;
	EA = 1;		  //ʹ���ж�
	ET0 = 1;	  //ʹ�ܶ�ʱ��0�ж�
	TR0 =1;		  //������ʱ��0�ж�
}
void LcdDisplay(int temp) 	 //lcd��ʾ
{
    
  	unsigned char datas[] = {0, 0, 0, 0, 0}; //��������
	float tp;  
	if(temp< 0)				//���¶�ֵΪ����
  	{
	  	LcdWriteCom(0xc6);		//д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('-');    //��ʾ��           
		temp=temp-1;		 //��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
  	}
 	else
  	{			
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
	}
	datas[0] = temp / 10000;
	datas[1] = temp % 10000 / 1000;
	datas[2] = temp % 1000 / 100;
	datas[3] = temp % 100 / 10;
	LcdWriteCom(0xca);		  //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[1]); //ʮλ
	LcdWriteData('0'+datas[2]); //��λ 
	LcdWriteData('.'); 		//��ʾ ��.��
	LcdWriteData('0'+datas[3]); //��ʾС����
	LcdWriteData(0xdf);
	LcdWriteData('C');   	 
}
void TimeDisplay()
{
    LcdWriteCom(0x82);
    LcdWriteData('0'+TIME[6]/16);				//��
	LcdWriteData('0'+(TIME[6]&0x0f));				 
	LcdWriteData('-');
    LcdWriteData('0'+TIME[4]/16);				//��
	LcdWriteData('0'+(TIME[4]&0x0f));				 
	LcdWriteData('-');	
    LcdWriteData('0'+TIME[3]/16);				//��
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0xc1);
    LcdWriteData('0'+TIME[2]/16);				//ʱ
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+TIME[1]/16);				//��
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+TIME[0]/16);				//��
	LcdWriteData('0'+(TIME[0]&0x0f));
	switch(TIME[5])															   //������ʾ
	{
	   case(1):LcdWriteCom(0x8b);
	            LcdWriteData('M');LcdWriteData('o');LcdWriteData('n');break;
	   case(2):LcdWriteCom(0x8b);
	            LcdWriteData('T');LcdWriteData('u');LcdWriteData('e');break;
	   case(3):LcdWriteCom(0x8b);
	            LcdWriteData('W');LcdWriteData('e');LcdWriteData('n');break;
	   case(4):LcdWriteCom(0x8b);
	            LcdWriteData('T');LcdWriteData('h');LcdWriteData('u');break;
	   case(5):LcdWriteCom(0x8b);
	            LcdWriteData('F');LcdWriteData('r');LcdWriteData('i');break;
	   case(6):LcdWriteCom(0x8b);
	            LcdWriteData('S');LcdWriteData('a');LcdWriteData('t');break;
	   case(7):LcdWriteCom(0x8b);
	            LcdWriteData('S');LcdWriteData('u');LcdWriteData('n');break;
	}
}
 void main()
{	
    Ds18b20Init();
    Timer0Init();
    Ds1302Init();
	LcdInit();		
	LcdWriteCom(0x80);	
	LcdWriteData('2');
	LcdWriteCom(0x81);	
	LcdWriteData('0');
	LcdWriteCom(0xcd);
	LcdWriteData('C');
	while(1)
	{
	  Ds1302ReadTime();
	}
}
void Timer0() interrupt 1
{
    uint time;
    TH0 = 0XFC;
	TL0 = 0X18;
	time++;
	if(time==100)      //��ʱ10ms		
	{
	    time = 0;
	   	LcdDisplay(Ds18b20ReadTemp());    //1602��ȡ�¶� 
	    TimeDisplay(); 
	}
}
