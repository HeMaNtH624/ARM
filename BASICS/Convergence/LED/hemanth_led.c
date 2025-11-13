#include<LPC21XX.H>
void delay_ms(int n)
{
	int i;
	for(;n>0; n--)
	for(i=12000; i>0; i--);
}

int main()
{
	PINSEL0 = 0;
	IODIR0 = 1<<0;
	IOSET0 = 1<<0;
	while(1)
	{
		IOCLR0 = 1<<0;
		delay_ms(500);
		IOSET0 = 1<<0;
		delay_ms(500);
	}
}

