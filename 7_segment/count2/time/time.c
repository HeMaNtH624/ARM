#include<LPC21XX.h>
void two_digit(int);
void two2_digit(int);
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

#define seg_d 0xFF
#define seg_1 1<<8
#define seg_2 1<<9
#define seg_3 1<<10
#define seg_4 1<<11
typedef unsigned char u8;
u8 lut[] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

int main()
{
	u8 min=0, sec=0;
	IODIR0 = seg_d;
	IODIR0 = seg_d|seg_1|seg_2|seg_3|seg_4;
	while(min<60 && sec<60)
	{
		two2_digit(sec++);
		if(sec==60)
		{
			sec = 0;
			two_digit(min++);
		}
		if(min==60)
		min=0;
	}
}

void two_digit(int n)
{
	u8 k;
	for(k=0; k<50; k++)
	{
		IOCLR0 = seg_d;
		IOSET0 = lut[(n/1000)];
		IOSET0 = seg_1;
		delay_ms(5);
		IOCLR0 = seg_1;
		
		IOCLR0 = seg_d;
		IOSET0 = lut[(n/100)%10];
		IOSET0 = seg_2;
		delay_ms(5);
		IOCLR0 = seg_2;

	}
}

void two2_digit(int n)
{
		u8 k;
		for(k=0; k<50; k++)
		{
			IOCLR0 = seg_d;
			IOSET0 = lut[(n/10)%10];
			IOSET0 = seg_3;
			delay_ms(5);
			IOCLR0 = seg_3;

			IOCLR0 = seg_d;
			IOSET0 = lut[(n%10)];
			IOSET0 = seg_4;
			delay_ms(5);
			IOCLR0 = seg_4;
		}

}