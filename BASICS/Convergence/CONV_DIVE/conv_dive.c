#include<LPC21XX.H>
#define LED 0xFF
void delay_seconds(int);
int main()
{
	int i, j, k, l;
	while(1)
	{
		j=7, l=4;
		IODIR0 = LED;

		for(i=0; i<=7; i++)
		{
			IOPIN0 = ~(1<<i | 1<<(7-i));
			delay_seconds(500);	

		}
	}
}

void delay_seconds(int n)
{
	int i;
	for(; n>0; n--)
	for(i=12000; i>0; i--);
}

