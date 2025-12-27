//#include<LPC21XX.H>
#include "lcd_header.h"
#define c0 (IOPIN0&(1<<0))
#define c1 (IOPIN0&(1<<1))
#define c2 (IOPIN0&(1<<2))
#define c3 (IOPIN0&(1<<3))

#define r0 1<<4
#define r1 1<<5
#define r2 1<<6
#define r3 1<<7

unsigned int keypad_arr[4][4]={{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};

unsigned int key_scan(void)
{
	unsigned char row_val, col_val;
	
	IODIR0|=r1|r0|r2|r3;
	IOCLR0|=c0|c1|c2|c3;
	
	while((c0&&c1&&c2&&c3)==1);
	
	while(1)
	{
		IOCLR0|=r0;
		IOSET0|=r1|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=0;
			break;
		}
		
		IOCLR0|=r1;
		IOSET0|=r0|r2|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=1;
			break;
		}
		
		IOCLR0|=r2;
		IOSET0|=r1|r0|r3;
		if((c0&&c1&&c2&&c3)==0)
		{
			row_val=2;
			break;
		}
		
		IOCLR0|=r3;
		IOSET0|=r1|r2|r0;
		if((c1&&c2&&c3&&c0)==0)
		{
			row_val=3;
			break;
		}
	}
	
	if(c0==0)
		col_val=0;
	
	else if(c1==0)
		col_val=1;
	
	else if(c2==0)
		col_val=2;
	
	else if(c3==0)
		col_val=3;
	
	delay_ms(150);
	
	while((c0&&c1&&c2&&c3)==0);
	return keypad_arr[row_val][col_val];
}

int main()
{
	unsigned int res;
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STR("4X4 KEYPAD");
	while(1)
	{
		LCD_CMD(0XC0);
		res=key_scan();
		LCD_DATA(res/10+48);
		LCD_DATA((res%10)+48);
		delay_ms(1000);
		
	}
}