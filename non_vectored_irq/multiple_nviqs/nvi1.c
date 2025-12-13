#include<lpc21xx.h>

void isr(void) __irq
{
	if((VICIRQStatus>>14)&1)
	{
		EXTINT = 0X01;
		IOSET0 = 1<<0;
		IOCLR0 = 1<<0;
		VICVectAddr = 0;
	}

	if((VICIRQStatus>>15)&1)
	{
		EXTINT = 0X03;
		IOSET0 = 1<<1;
		IOCLR0 = 1<<1;
		VICVectAddr = 0;
	}

	if((VICIRQStatus>>16)&1)
	{
		EXTINT = 0X07;
		IOSET0 = 1<<2;
		IOCLR0 = 1<<2;
		VICVectAddr = 0;
	}

	if((VICIRQStatus>>17)&1)
	{
		EXTINT = 0X0F;
		IOSET0 = 1<<3;
		IOCLR0 = 1<<3;
		VICVectAddr = 0;
	}
}



int main()
{
	unsigned int count = 0;
	IODIR0 = 1<<0|1<<1|1<<2|1<<3;

	PINSEL0 = 0XA00C0000;
	PINSEL1 = 0X01;

	VICIntSelect = 0<<14|0<<15|0<<16|0<<17;

	VICDefVectAddr = (unsigned long)isr;

	EXTMODE = 0X00;
	EXTPOLAR = 0X00;

	VICIntEnable = 1<<14|1<<15|1<<16|1<<17;

	while(1)
	{
		count++;
		if(count == 10000)
		count = 0;
	}
	
}