#include<LPC21XX.H>

#define LCD 0XF<8
#define RS 1<<12
#define EN 1<<13

void delay_ms(unsigned int n)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<n);
	T0TCR=0X03;
	T0TCR=0X00;
}

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);

void LCD_INIT(void)
{
	IODIR0|=LCD|RS|EN;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X28);
}

void LCD_DATA(unsigned char d)
{
	IOCLR0|=LCD;
	IOSET0|=((d>>4)&0xf)<<8;
	IOSET0|=RS;
	IOSET0|=EN;
	delay_ms(2);
	IOCLR0|=EN;

	IOCLR0|=LCD;
	IOSET0|=(d&0xf)<<8;
	IOSET0|=RS;
	IOSET0|=EN;
	delay_ms(2);
	IOCLR0|=EN;
}

void LCD_CMD(unsigned char d)
{
	IOCLR0|=LCD;
	IOSET0|=((d>>4)&0xf)<<8;
	IOCLR0|=RS;
	IOSET0|=EN;
	delay_ms(2);
	IOCLR0|=EN;

	IOCLR0|=LCD;
	IOSET0|=(d&0xf)<<8;
	IOCLR0|=RS;
	IOSET0|=EN;
	delay_ms(2);
	IOCLR0|=EN;
}

void LCD_STR(unsigned char *s)
{
 	while(*s)
	LCD_DATA(*s++);
}