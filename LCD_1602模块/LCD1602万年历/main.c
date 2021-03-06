
#include"lcd.h"
#include"temp.h"
#include"DS1302.h"

void Timer0Init()
{
    TMOD |= 0X01;	//定时器0工作方式1
	TH0 = 0XFC;		//定时1us
	TL0 = 0X18;
	EA = 1;		  //使能中断
	ET0 = 1;	  //使能定时器0中断
	TR0 =1;		  //开启定时器0中断
}
void LcdDisplay(int temp) 	 //lcd显示
{
    
  	unsigned char datas[] = {0, 0, 0, 0, 0}; //定义数组
	float tp;  
	if(temp< 0)				//当温度值为负数
  	{
	  	LcdWriteCom(0xc6);		//写地址 80表示初始地址
	    LcdWriteData('-');    //显示负           
		temp=temp-1;		 //因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算由�0.5，还是在小数点后面。
  	}
 	else
  	{			
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		//如果温度是正的那么，那么正数的原码就是补码它本身
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
	}
	datas[0] = temp / 10000;
	datas[1] = temp % 10000 / 1000;
	datas[2] = temp % 1000 / 100;
	datas[3] = temp % 100 / 10;
	LcdWriteCom(0xca);		  //写地址 80表示初始地址
	LcdWriteData('0'+datas[1]); //十位
	LcdWriteData('0'+datas[2]); //个位 
	LcdWriteData('.'); 		//显示 ‘.’
	LcdWriteData('0'+datas[3]); //显示小数点
	LcdWriteData(0xdf);
	LcdWriteData('C');   	 
}
void TimeDisplay()
{
    LcdWriteCom(0x82);
    LcdWriteData('0'+TIME[6]/16);				//年
	LcdWriteData('0'+(TIME[6]&0x0f));				 
	LcdWriteData('-');
    LcdWriteData('0'+TIME[4]/16);				//月
	LcdWriteData('0'+(TIME[4]&0x0f));				 
	LcdWriteData('-');	
    LcdWriteData('0'+TIME[3]/16);				//日
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0xc1);
    LcdWriteData('0'+TIME[2]/16);				//时
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+TIME[1]/16);				//分
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+TIME[0]/16);				//秒
	LcdWriteData('0'+(TIME[0]&0x0f));
	switch(TIME[5])															   //星期显示
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
	if(time==100)      //定时10ms		
	{
	    time = 0;
	   	LcdDisplay(Ds18b20ReadTemp());    //1602读取温度 
	    TimeDisplay(); 
	}
}
