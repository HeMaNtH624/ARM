#include<lpc21xx.h>
#define led 1<<0

unsigned int hemanth __attribute__((at(0xE0028008)));
unsigned int udhaya __attribute__((at(0XE0028004)));

void delay_ms(int n)
{
	int i;
	for(;n>0; n--)
	{
		for(i=12000; i>=0; i--);
	}
}

int main()
{
 	while(1)
	{				   
	hemanth = led;
	udhaya = led;
	delay_ms(500);
	IOCLR0 = led;
	delay_ms(500);
	}
}