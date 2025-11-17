#include<LPC21XX.H>
#include "delay.h"
#define RS 1<<8
#define LCD 0xFF
#define E 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void STRING(unsigned char *);

int main()
{
	LCD_INIT();
	LCD_CMD(0x80);
	STRING("Embedded systems chennai india vector");
}

void LCD_INIT(void)
{
	IODIR0 = LCD | RS | E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
}

void LCD_CMD(unsigned char cmd)
{
	IOPIN0 = cmd;
	IOCLR0 = RS;
	IOSET0 = E;
	delay(2);
	IOCLR0 = E;
}

void LCD_DATA(unsigned char d)
{
	IOPIN0 = d;
	IOSET0 = RS;
	IOSET0 = E;
	delay(2);
	IOCLR0 = E;
}

void STRING(unsigned char *s)
{
	int count = 0;
	while(*s)
	{
		LCD_DATA(*s++);
		count++;
		if(count==20)
		LCD_CMD(0xc0);

	}
}



