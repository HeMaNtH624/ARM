#include<LPC21XX.H>

#include "delay.h"

#define LCD_D 0xFF

#define RS 1<<8

#define E 1<<9


void LCD_INIT(void);

void LCD_CMD(unsigned char);

void LCD_DATA(unsigned char);


int main()

{
	int i;

	LCD_INIT();
	while(1)
	{

		LCD_CMD(0x80);
		for(i='A'; i<='Z'; i++)
		{
			LCD_DATA('A');
			delay(500);
		}
	}

}


void LCD_INIT(void)

{

	IODIR0 = (LCD_D|RS)|E;

	LCD_CMD(0x01);

	LCD_CMD(0x02) ;

	LCD_CMD(0xc);

	LCD_CMD(0x38);

}


void LCD_CMD(unsigned char cmd)

{

	IOPIN0 = cmd;

	IOCLR0 = RS;

	IOSET0 = E;

	delay(500);

	IOCLR0 = E;

}


void LCD_DATA(unsigned char d)

{

	IOPIN0 = d;

	IOSET0 = RS;

	IOSET0 = E;

	delay(500);

	IOCLR0 = E;

}



