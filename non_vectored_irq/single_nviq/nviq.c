#include<lpc21xx.h>
unsigned int iodir __attribute((at(0xE0028008)));
unsigned int ioset __attribute((at(0XE0028004)));

void isr(void) __irq
{
	EXTINT = 0X01;
	ioset = 1<<0;
	IOCLR0 = 1<<0;
	VICVectAddr = 0;	
}

int main()
{
	unsigned int count = 0;
	iodir=1<<0;
	PINSEL1 = 0X01;

	VICIntSelect = 14<<0;

	VICDefVectAddr = (unsigned long)isr;

	EXTMODE = 0X00;
	EXTPOLAR = 0X00;

	VICIntEnable = 1<<14;

	while(1)
	{
		count++;
		if(count==1000)
		count = 0;
	}

}