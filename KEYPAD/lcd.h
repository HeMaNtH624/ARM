
//#include "delay.h"
#define LCD_D 0xff
#define RS 1<<8
#define EN 1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);
void LCD_INTEGER(int );
void LCD_FLOAT( float f);
void delay(int n)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<n);
	T0TCR=0X03;
	T0TCR=0X00;
}
void LCD_INIT(void)

{
	IODIR0 = LCD_D | RS | EN;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
}


void LCD_CMD(unsigned char cmd)
{
	IOPIN0 = cmd;
	IOCLR0 = RS;
	IOSET0 = EN;
	delay(2);
	IOCLR0 = EN;
}

void LCD_DATA(unsigned char d)
{
	IOPIN0 = d;
	IOSET0 = RS;
	IOSET0 = EN;
	delay(2);
	IOCLR0 = EN;
}

void LCD_INTEGER(int n)
{ 
	unsigned char a[5];
	signed char i = 0; 
	if(n==0)
	LCD_DATA('0');

	else
	{
		if(n<0)

		{
			LCD_DATA('-');
			n = -n;
		}

		while(n>0)
		{
			a[i++] = n%10;
			n = n/10;
		}

		for(--i; i>=0; i--) 
		LCD_DATA(a[i] + 48);
	}

}

void LCD_FLOAT( float f)
{
	int x = f;
	LCD_INTEGER(x);
	LCD_DATA('.');
	f = (f-x)*10;
	LCD_INTEGER(f);
}

void LCD_STR(unsigned char *s)
{
	int count = 0;
	while(*s)
	{
		LCD_DATA(*s++);
		count++;
		if(count==20)
		LCD_CMD(0xc0);

	}
}
	   

