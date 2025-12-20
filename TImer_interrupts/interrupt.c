#include<LPC21XX.H>
#define sw 14
int flag = 0;
void isr0(void) __irq
{
	T0IR = 0X01;
	if(flag==0)
	{
		IOSET0 = 1<<0;
		flag = 1;
	}
	else
	{
		IOCLR0 = 1<<0;
		flag = 0;
	}
	VICVectAddr = 0;
}

int main()
{
	IODIR0 = 1<<0 | 1<<1;
	T0MR0 = 7500000-1;
	T0MCR = 0X03;
	
	VICIntSelect = 0;
	VICVectCntl0 = (0x20)|4;
	VICVectAddr0 = (unsigned long)isr0;
	VICIntEnable = 1<<4;
	T0TCR = 0X01;
	while(1)
	{
		if(((IOPIN0>>sw)&1)==0)
 		IOSET0 = 1<<1;

		else
		IOCLR0 = 1<<1;
	}
}									        