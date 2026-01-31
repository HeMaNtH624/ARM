#include "lcd_header.h"
void UART_TX(unsigned char);
void UART_CONFIG(void);
unsigned char UART_RX(void);
void UART_STR(unsigned char *);

int main()
{
	
	unsigned char ch[16], rxByte;
	int i;
	PINSEL0|=0X05;
	UART_CONFIG();
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STR("UART testing...");
	while(1)
	{
		i=0;
		while(1)
		{
			rxByte=UART_RX();
			if(rxByte!='\r' || rxByte!='\n')
			{
				ch[i]='\0';
				break;
			}	
			else 
			ch[i++]=rxByte;
		}
		LCD_CMD(0XC0);
		LCD_STR(ch);
		UART_STR(ch);
	}		
}

void UART_CONFIG(void)
{
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}

void UART_TX(unsigned char d)
{
	U0THR=d;
	while(((U0LSR>>5)&1)==0);
}

unsigned char UART_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}

void UART_STR(unsigned char *d)
{
	while(*d)
	UART_TX(*d++);
}
