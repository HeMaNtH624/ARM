#include<LPC21XX.H>
#define led 1<<16
#define sw 14

void delay_ms(n)
{
	int i;
	for(;n>0; n--)
	for(i=12000; i>=0; i--);
}

void UART_CONFIG(void);
void UART_TX(char);
void UART_STR(char *);
void isr0(void) __irq
{
	int temp;
	temp = U0IIR;
	UART_STR("KUMAR");
	VICVectAddr=0;
}

int main()
{
	IODIR0=led;
	PINSEL0|=0X05;
	UART_CONFIG();

	VICIntSelect=0;
	VICVectCntl0=(0x20)|6;
	VICVectAddr0=(unsigned long)isr0;
	U0IER=1<<1;
	VICIntEnable=1<<6;
	//UART_STR("Hemanth");

	while(1)
	{
		//if(((IOPIN0>>sw)&1)==0)
		{
			IOCLR0=led;
			delay_ms(500);
		}
	//	else
		{
			 IOSET0=led;
			 delay_ms(500);
		}
	}
}

void UART_CONFIG(void)
{
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}

void UART_STR(char *n)
{
	while(*n)
	{
		UART_TX(*n++);
	}
}

void UART_TX(char n)
{
	U0THR=n;
	while(((U0LSR>>5)&1)==0);
}