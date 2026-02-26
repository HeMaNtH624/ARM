#include<lpc21xx.h>
#define sw1 1<<14
#define sw2 1<<15
#define sw3 1<<16
#define led 7

void delay_ms(int ms)
{
	unsigned int i;
	for(; ms>=0; ms--)
	for(i=12000; i>=0; i--);
}

unsigned long int x=0;
int main()
{
	
	PINSEL1|=0X400;
	//IODIR0|=led;
	PWMMR0=15000-1;
	PWMMR5=0;
	PWMMCR=0X00002;
	PWMPCR=0X02000;
	PWMTCR=0X00009;
//	PWMLER=0X00000020;

	/*while(1)
	{
		while(PWMIR!=0X0001);
		PWMIR=0X01;
		PWMMR5=x;
		if(x>=PWMMR0)
		x=0;
		x=x+50;
		PWMLER=0X0020;
	}
	*/
	while(1)
	{
		while(PWMIR!=0X0001);
		PWMIR=0X00000001;
		if(((IOPIN0>>sw1)&1)==0)
		{	
			delay_ms(200);
			PWMMR5=15000-1;
			while(((IOPIN0>>sw1)&1)==0);
			PWMLER=0X00000020;
		}

		else if(((IOPIN0>>sw2)&1)==0)
		{	
			delay_ms(200);
			PWMMR5=7500;
			while(((IOPIN0>>sw2)&1)==0);
			PWMLER=0X00000020;
		}

		else if(((IOPIN0>>sw3)&1)==0)
		{
			delay_ms(200);	
			PWMMR5=0;
			while(((IOPIN0>>sw3)&1)==0);
			PWMLER=0X00000020;
		}

		
//		delay_ms(200);
	} 
}


/*
#include<lpc21xx.h>
#define sw1 14
#define sw2 15
#define sw3 16
int main()
{
	
	PINSEL1|=0X400;
	//IODIR0|=led;
	PWMMR0=15000-1;
	//PWMMR0=15000-1;
	PWMLER=0X02;
	while(1)
	{
		if(((IOPIN0>>sw1)&1)==0)
		{
			PWMMR5=7500;
			PWMMCR=0X00002;
			PWMPCR=0X02000;
			PWMTCR=0X00009;
		}

		else if(((IOPIN0>>sw2)&1)==0)
		{
			PWMMR5=3750;
			PWMMCR=0X00002;
			PWMPCR=0X02000;
			PWMTCR=0X00009;
		}

		else if(((IOPIN0>>sw3)&1)==0)
		{
			PWMMR5=0;
			PWMMCR=0X00002;
			PWMPCR=0X02000;
			PWMTCR=0X00009;
		}
		PWMLER=0X020;
}	
}
*/