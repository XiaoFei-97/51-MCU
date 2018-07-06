#ifndef _LCD_H_
#define _LCD_H_
#include <reg52.h>

#ifndef uchar	  
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define LCD_DATA P0
sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;

void delay(u16);
void LCDWrite_cmd (uchar cmd);
void LCDWrite_data (uchar dat)
void LCD_1602Init();

#endif