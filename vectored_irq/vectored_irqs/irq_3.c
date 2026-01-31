#include<LPC21XX.H>
void isr0(void) __irq
{
	EXTINT = 0X01;
	IOSET0 = 1<<0;
	IOCLR0 = 1<<0;
	VICVectAddr = 0;
}

void isr1(void) __irq
{
	EXTINT = 0X03;
	IOSET0 = 1<<1;
	IOCLR0 = 1<<1;
	VICVectAddr = 0;
}

void isr2(void) __irq
{
	EXTINT = 0X07;
	IOSET0 = 1<<2;
	IOCLR0 = 1<<2;
	VICVectAddr = 0;
}

void isr3(void) __irq
{
	EXTINT = 0XFF;
	IOSET0 = 1<<3;
	IOCLR0 = 1<<3;
	VICVectAddr = 0;
}

int main()
{
	unsigned int count = 0;
	IODIR0 = 1<<0|1<<1|1<<2|1<<3;
	PINSEL0 = 0XA00C0000;
	PINSEL1 = 0X01;

	VICIntSelect = 0<<14|0<<15|0<<16|0<<17;
	
	VICVectCntl0 = 0x20|14;
	VICVectAddr0 = (unsigned long)isr0;

	VICVectCntl1 = 0x20|15;
	VICVectAddr1 = (unsigned long)isr1;

	VICVectCntl3 = 0x20|16;
	VICVectAddr3 = (unsigned long)isr2;

	VICVectCntl2 = 0x20|17;
	VICVectAddr2 = (unsigned long)isr3;

	EXTMODE = 0XFF;
	EXTPOLAR = 0X00;

	VICIntEnable = 1<<14|1<<15|1<<16|1<<17;

	while(1)
	{
		count++;
		if(count==10000)
		count=0;	
	}
}

