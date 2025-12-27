#include<LPC21XX.H>

#define LCD 0X0F<<14
#define RS 1<<8
#define EN 1<<9

void delay_ms(int ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}

void LCD_INIT(void);
void LCD_DATA(unsigned char);
void LCD_CMD(unsigned char );
void LCD_STR(unsigned char *);

void LCD_INIT(void)
{
	IODIR0|=LCD|RS|EN;
	LCD_CMD(0X01);
	LCD_CMD(0X02);
	LCD_CMD(0X0C);
	LCD_CMD(0X38);
}

void LCD_DATA(unsigned char d)
{
	IOCLR0=LCD;
	IOSET0=((d>>4)&0x0f)<<14;
	IOSET0=RS;
	IOSET0=EN;
	delay_ms(2);
	IOCLR0=EN;
	
	IOCLR0=LCD;
	IOSET0=(d&0x0f)<<14;
	IOSET0=RS;
	IOSET0=EN;
	delay_ms(2);
	IOCLR0=EN;
}

void LCD_CMD(unsigned char d)
{
	IOCLR0=LCD;
	IOSET0=((d>>4)&0x0f)<<14;
	IOCLR0=RS;
	IOSET0=EN;
	delay_ms(2);
	IOCLR0=EN;
	
	IOCLR0=LCD;
	IOSET0=(d&0x0f)<<14;
	IOCLR0=RS;
	IOSET0=EN;
	delay_ms(2);
	IOCLR0=EN;
}

void LCD_STR(unsigned char *s)
{
	while(*s)
		LCD_DATA(*s++);
}