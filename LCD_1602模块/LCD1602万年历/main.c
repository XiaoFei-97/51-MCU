
#include"lcd.h"
#include"temp.h"
#include"DS1302.h"

void Timer0Init()
{
    TMOD |= 0X01;	//¶¨Ê±Æ÷0¹¤×÷·½Ê½1
	TH0 = 0XFC;		//¶¨Ê±1us
	TL0 = 0X18;
	EA = 1;		  //Ê¹ÄÜÖÐ¶Ï
	ET0 = 1;	  //Ê¹ÄÜ¶¨Ê±Æ÷0ÖÐ¶Ï
	TR0 =1;		  //¿ªÆô¶¨Ê±Æ÷0ÖÐ¶Ï
}
void LcdDisplay(int temp) 	 //lcdÏÔÊ¾
{
    
  	unsigned char datas[] = {0, 0, 0, 0, 0}; //¶¨ÒåÊý×é
	float tp;  
	if(temp< 0)				//µ±ÎÂ¶ÈÖµÎª¸ºÊý
  	{
	  	LcdWriteCom(0xc6);		//Ð´µØÖ· 80±íÊ¾³õÊ¼µØÖ·
	    LcdWriteData('-');    //ÏÔÊ¾¸º           
		temp=temp-1;		 //ÒòÎª¶ÁÈ¡µÄÎÂ¶ÈÊÇÊµ¼ÊÎÂ¶ÈµÄ²¹Âë£¬ËùÒÔ¼õ1£¬ÔÙÈ¡·´Çó³öÔ­Âë
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//ÁôÁ½¸öÐ¡Êýµã¾Í*100£¬+0.5ÊÇËÄÉáÎåÈë£¬ÒòÎªCÓïÑÔ¸¡µãÊý×ª»»ÎªÕûÐÍµÄÊ±ºò°ÑÐ¡Êýµã
		//ºóÃæµÄÊý×Ô¶¯È¥µô£¬²»¹ÜÊÇ·ñ´óÓÚ0.5£¬¶ø+0.5Ö®ºó´óÓÚ0.5µÄ¾ÍÊÇ½ø1ÁË£¬Ð¡ÓÚ0.5µÄ¾Í
		//ËãÓÉÏ0.5£¬»¹ÊÇÔÚÐ¡ÊýµãºóÃæ¡£
  	}
 	else
  	{			
		tp=temp;//ÒòÎªÊý¾Ý´¦ÀíÓÐÐ¡ÊýµãËùÒÔ½«ÎÂ¶È¸³¸øÒ»¸ö¸¡µãÐÍ±äÁ¿
		//Èç¹ûÎÂ¶ÈÊÇÕýµÄÄÇÃ´£¬ÄÇÃ´ÕýÊýµÄÔ­Âë¾ÍÊÇ²¹ÂëËü±¾Éí
		temp=tp*0.0625*100+0.5;	
		//ÁôÁ½¸öÐ¡Êýµã¾Í*100£¬+0.5ÊÇËÄÉáÎåÈë£¬ÒòÎªCÓïÑÔ¸¡µãÊý×ª»»ÎªÕûÐÍµÄÊ±ºò°ÑÐ¡Êýµã
		//ºóÃæµÄÊý×Ô¶¯È¥µô£¬²»¹ÜÊÇ·ñ´óÓÚ0.5£¬¶ø+0.5Ö®ºó´óÓÚ0.5µÄ¾ÍÊÇ½ø1ÁË£¬Ð¡ÓÚ0.5µÄ¾Í
		//Ëã¼ÓÉÏ0.5£¬»¹ÊÇÔÚÐ¡ÊýµãºóÃæ¡£
	}
	datas[0] = temp / 10000;
	datas[1] = temp % 10000 / 1000;
	datas[2] = temp % 1000 / 100;
	datas[3] = temp % 100 / 10;
	LcdWriteCom(0xca);		  //Ð´µØÖ· 80±íÊ¾³õÊ¼µØÖ·
	LcdWriteData('0'+datas[1]); //Ê®Î»
	LcdWriteData('0'+datas[2]); //¸öÎ» 
	LcdWriteData('.'); 		//ÏÔÊ¾ ¡®.¡¯
	LcdWriteData('0'+datas[3]); //ÏÔÊ¾Ð¡Êýµã
	LcdWriteData(0xdf);
	LcdWriteData('C');   	 
}
void TimeDisplay()
{
    LcdWriteCom(0x82);
    LcdWriteData('0'+TIME[6]/16);				//Äê
	LcdWriteData('0'+(TIME[6]&0x0f));				 
	LcdWriteData('-');
    LcdWriteData('0'+TIME[4]/16);				//ÔÂ
	LcdWriteData('0'+(TIME[4]&0x0f));				 
	LcdWriteData('-');	
    LcdWriteData('0'+TIME[3]/16);				//ÈÕ
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0xc1);
    LcdWriteData('0'+TIME[2]/16);				//Ê±
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData(':');
	LcdWriteData('0'+TIME[1]/16);				//·Ö
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData(':');
	LcdWriteData('0'+TIME[0]/16);				//Ãë
	LcdWriteData('0'+(TIME[0]&0x0f));
	switch(TIME[5])															   //ÐÇÆÚÏÔÊ¾
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
	if(time==100)      //¶¨Ê±10ms		
	{
	    time = 0;
	   	LcdDisplay(Ds18b20ReadTemp());    //1602¶ÁÈ¡ÎÂ¶È 
	    TimeDisplay(); 
	}
}
