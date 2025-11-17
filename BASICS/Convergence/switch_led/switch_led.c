#include<LPC21XX.H>
#define sw1 14
#define sw2 15
#define sw3 16
#define led1 1<<17
#define led2 1<<18
#define led3 1<<19
void delay(int n);
int main()
{
	IODIR0 = (led1 | led2)|led3;
	while(1)
	{
		if(((IOPIN0>>sw1)&1)==0)
		IOCLR0 = led1;

		else if(((IOPIN0>>sw2)&1)==0)
		IOCLR0 = led2;

		else if(((IOPIN0>>sw3)&1)==0)
		IOCLR0 = led3;

		else 
		IOSET0 = (led1|led2)|led3;
	}
}
