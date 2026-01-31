#include<LPC21XX.H>
#include "lcd_header.h"
void UART_CONFIG(void);
void UART_TX(unsigned char );
void UART_STR(unsigned char *);
unsigned char UART_RX(void);

int main()
{
	unsigned char rxByte, txByte;
	PINSEL0|=0X00000005;
	UART_CONFIG();
	LCD_INIT();
	while(1)
	{
		rxByte = UART_RX();
		//rxByte = rxByte^32;
		UART_TX(rxByte);
		LCD_CMD(0X80);
		LCD_DATA(rxByte);
	}
}

void UART_CONFIG(void)
{
	U0LCR = 0X83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0X03;
}

void UART_TX(unsigned char n)
{
	U0THR = n;
	while(((U0LSR>>5)&1)==0);
}

void UART_STR(unsigned char *s)
{
	while(*s)
	UART_TX(*s++);
}

unsigned char UART_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}

