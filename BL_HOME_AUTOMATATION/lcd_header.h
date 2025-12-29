#include<LPC21XX.H>


#define RS 1<<14

#define LCD 0xF<<8

#define EN 1<<15


void delay(int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}


void LCD_INIT(void);

void LCD_CMD(unsigned char);

void LCD_DATA(unsigned char);

void STRING(unsigned char *);


void LCD_INIT(void)

{

	IODIR0 = LCD | RS | EN;

	LCD_CMD(0x01);

	LCD_CMD(0x02);

	LCD_CMD(0x0c);

	LCD_CMD(0x28);

}


void LCD_CMD(unsigned char cmd)

{

	IOCLR0 = LCD;
	IOSET0 = ((cmd>>4)&0x0f)<<8;

	IOCLR0 = RS;

	IOSET0 = EN;

	delay(2);

	IOCLR0 = EN;

	IOCLR0 = LCD;
	IOSET0 = (cmd&0x0f)<<8;

	IOCLR0 = RS;

	IOSET0 = EN;

	delay(2);

	IOCLR0 = EN;

}


void LCD_DATA(unsigned char d)

{

	IOCLR0=LCD;
	IOSET0=((d>>4)&0x0f)<<8;

	IOSET0 = RS;

	IOSET0 = EN;

	delay(2);

	IOCLR0 = EN;

	IOCLR0=LCD;
	IOSET0=(d&0x0f)<<8;

	IOSET0 = RS;

	IOSET0 = EN;

	delay(2);

	IOCLR0 = EN;

}




void STRING(unsigned char *s)

{

	int count = 0;

	while(*s)

	{
		LCD_DATA(*s++);

	}

}




