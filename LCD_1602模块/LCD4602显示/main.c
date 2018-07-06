#include "reg52.h"
#include "1602.h"



void main()
{ RW = 0;
  RS = 0;
  
  EN = 0;
   LCD_1602Init();
  
   LCDWrite_cmd (0xc0);
   LCDWrite_data('T');
   LCDWrite_cmd (0xc1);
   LCDWrite_data('e');
   LCDWrite_cmd (0xc2);
   LCDWrite_data('m');
   LCDWrite_cmd (0xc3);
   LCDWrite_data('p');
   LCDWrite_cmd (0xc4);
   LCDWrite_data(':');
   while(1);
}

