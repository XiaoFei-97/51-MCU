/**************************************************************************************
*		              DA-PWM输出实验												  *
实现现象：下载程序后DA模块上的指示灯呈呼吸灯效果，由暗变亮再由亮变暗
注意事项：要将AD/DA模块上的短接片将OUT和LED短接，板子丝印上有。
		  如果不想让点阵模块显示，可以将74HC595模块上的JP595短接片拔掉。																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

//--定义使用的IO口--//
sbit PWM=P2^1;
bit DIR;

//--定义一个全局变量--// 
u16 count,value,timer1;

/*******************************************************************************
* 函 数 名         : Timer1Init
* 函数功能		   : 定时器1初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer1Init()
{
	TMOD|=0X10;//选择为定时器1模式，工作方式1，仅用TR1打开启动。

	TH1 = 0xFF; 
	TL1 = 0xff;   //1us
		
	ET1=1;//打开定时器1中断允许
	EA=1;//打开总中断
	TR1=1;//打开定时器			
}


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	Timer1Init();  //定时器1初始化
	while(1)
	{
		if(count>100)							
		{  
			count=0;
			if(DIR==1)					   //DIR控制增加或减小
			{
			  value++;
			}			
			if(DIR==0)
			{
			  value--;
			}
		}
		    
		if (value==1000)
		{
			DIR = 0;
		}	
		if(value == 0)
		{
			DIR = 1;
	    }
		if(timer1>1000)
		{
		    timer1 = 0;
		}
		if(timer1<value)
		{
		     PWM = 1;
		}
		else
		{
		   PWM = 0;
		}
	}
}


void Time1(void) interrupt 3
{
    TH1 = 0xFF; 
	TL1 = 0xff;

	timer1++;
	count++; 

}