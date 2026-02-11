#include<lpc21xx.h>

void float_point(float); 
void four_digit(int);

#define seg_d 0xff
#define seg_1 1<<8
#define seg_2 1<<9
#define seg_3 1<<10 
#define seg_4 1<<11  

int dp1=0, dp2=0, dp3=0; 

unsigned char arr[]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void delay_ms(int ms)
{
	int i;
	for(;ms>=0; ms--)
	{
		for(i=12000; i>=0; i--);
	}
}


int main()
{
	IODIR0|=seg_d|seg_1|seg_2|seg_3|seg_4;
	while(1)
	{
		float_point(15.67);
	}
}


void float_point(float f)
{
	int temp=f;
	if(f==0)
	{
		four_digit(0);
	}
	
	if(f>0&&f<10.0)
	{
		dp1=0x80;
		temp=f*1000;
	}
	
	else if(f>=10.0&&f<100.0)
	{
		dp2=0x80;
		temp=f*100;
	}
	
	else if(f>=100.0&&f<1000.0)
	{
		dp3=0x80;
		temp=f*10;
	}
	four_digit(temp);
}


void four_digit(int n)
{
	int k;
	for(k=0; k<50; k++)
	{
		IOCLR0|=seg_d;
		IOSET0|=arr[n/1000]^dp1;
		IOCLR0|=seg_1;
		delay_ms(3);
		IOSET0|=seg_1;
		
		IOCLR0|=seg_d;
		IOSET0|=arr[(n/100)%10]^dp2;
		IOCLR0|=seg_2;
		delay_ms(3);
		IOSET0|=seg_2;
		
		IOCLR0|=seg_d;
		IOSET0|=arr[(n/10)%10]^dp3;
		IOCLR0|=seg_3;
		delay_ms(3);
		IOSET0|=seg_3;
		
		IOCLR0|=seg_d;
		IOSET0|=arr[n%10];
		IOCLR0|=seg_4;
		delay_ms(3);
		IOSET0|=seg_4;
	}

}



