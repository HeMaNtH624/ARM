#include <lpc21xx.h>
#include "lcd_header.h"
#define MSTR 5
#define LSBF 6
#define SPIE 7 
//#define SPIF 7
#define CS 7

#define mode0 0x00
#define mode1 0x08
#define mode2 0x10
#define mode3 0x18

void delay_ms(int ms)
{
	int i;
	for(ms; ms>0; ms--)
	{
		for(i=12000; i>=0; i--);
	}
}
typedef unsigned char u8;

void spi_init(void)
{
	PINSEL0|=0X00001500;
	S0SPCCR=150;
	S0SPCR=(1<<MSTR)|mode0;
	IODIR0|=1<<CS;
	IOSET0|=1<<CS;
}

u8 spi_wr(u8 ch)
{
	u8 spif;
	spif=S0SPSR;
	S0SPDR=ch;
	while(((S0SPSR>>SPIE)&1)==0);
	return S0SPDR;
}

float adc_mcp(u8 ch_no)
{
	u8 lByte, hByte;
	float adc;
	IOCLR0|=1<<CS;
	spi_wr(0x06);
	hByte=spi_wr(ch_no<<6);
	lByte=spi_wr(0x00);
	IOSET0|=1<<CS;
	adc=((hByte&0x0f)<<8)|lByte;
	adc=(adc*3.3)/4096;
	return adc;
}

int main()
{
	float f, temp;
	IODIR0|=1<<16;
	IOSET0|=1<<16;
	spi_init();
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STRING("  SPI   ");
	while(1)
	{
		f=adc_mcp(0);
		temp=f/0.01;
		LCD_CMD(0XC0);
		LCD_float(temp);
		if(temp>25.0)
		{
			IOCLR0|=1<<16;
		}

		else
		{
			IOSET0|=1<<16;
		}
	 	delay_ms(500);	
	}
}