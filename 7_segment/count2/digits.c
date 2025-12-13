#include<LPC21XX.h>
void delay_ms(unsigned int n)
{
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC<n);
	T0TCR = 0X03;
	T0TCR = 0X00;
}

void delay_S(unsigned int n)
{
	T0PR = 15000000-1;
	T0TCR = 0X01;
	while(T0TC<n);
	T0TCR = 0X03;
	T0TCR = 0X00;
}

#define seg_d 0xFF;
unsigned char lut[] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

int main()
{
	unsigned char dig = 0;
	IODIR0 = seg_d;
	while(dig<10)
	{
		IOCLR0 = seg_d;
		IOSET0 = lut[dig++];
		delay_ms(500); 
	}
}