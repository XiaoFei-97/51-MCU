#include "1602.h"
void delay(u16 num)
{
   u16 x,y;
   for(x=num; x>0; x--)
       for(y=110; y>0; y--);
}

void LCDWrite_cmd (u8 cmd)
{
   RS = 0;
   RW = 0;
   DATA = cmd;
   delay(5);
   EN = 1;
   delay(5);
   EN = 0;
}

void LCDWrite_data (u8 dat)
{
   RS = 1;
   RW = 0;
   DATA = dat;
   delay(5);
   EN = 1;
   delay(5);
   EN = 0;
}

void LCD_1602Init()
{
   LCDWrite_cmd (0x02);
   LCDWrite_cmd (0x06);
   LCDWrite_cmd (0x0c);
   LCDWrite_cmd (0x38);
   LCDWrite_cmd (0x01); 
}
