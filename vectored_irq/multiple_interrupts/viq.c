#include<LPC21XX.H>
 
void isr_int0(void) __irq
{
	EXTINT = 0X01;
	IOSET0 = 1<<0;
	IOCLR0 = 1<<0;
	VICVectAddr = 0;
}

void isr_int1(void) __irq
{
	EXTINT = 0X03;
	IOSET0 = 1<<1;
	IOCLR0 = 1<<1;
	VICVectAddr = 0;

}


int main()
{
	unsigned int count = 0;
	
	PINSEL1 = 0X01;
	IODIR0 = 1<<0 | 1<<1;
	PINSEL0 = 0X20000000;



	VICIntSelect = 0<<14|0<<15;

	VICVectCntl0 = (0x20)|14;
	VICVectAddr0 = (unsigned long)isr_int0;

	VICVectCntl1 = (0x20)|15;
	VICVectAddr1 = (unsigned long)isr_int1;

	EXTMODE = 0X00;
	EXTPOLAR = 0X03;

	VICIntEnable = 1<<14|1<<15;

	while(1)
	{
		count++;
	}

}