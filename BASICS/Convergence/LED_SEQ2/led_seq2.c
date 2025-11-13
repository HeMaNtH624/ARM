#include<LPC21XX.H>
#define AL_LED 0xFF
void delay(int n)
{
	int i;
	for(;n>0; n--)
	for(i=12000; i>0; i--);
}

int main()
{	int i;
	while(1)
	{
		IODIR0 = AL_LED;
	    IOSET0 = AL_LED;
		for(i=7; i>=0; i--)
		{
			IOCLR0 = 1<<i;
			delay(500);
		}
		IOSET0 = AL_LED;
		delay(500);
	}
}
