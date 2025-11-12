#include<LPC21XX.H>
#define LED 0xFF;
void delay(int n)
{
	int i;
	for(; n>0; n--)
	for(i=12000; i>0; i--);
}						   

int main()
{
	int i, j;
	while(1)
	{	j=7;
		IODIR0 = LED;
		IOSET0 = LED;
		for(i=0; i<=3; i++)
		{ 	
			IOCLR0 = 1<<i | 1<<j;
			j--;
			delay(500); 
		}
		IOSET0 = LED;
		delay(500);
	}
}
