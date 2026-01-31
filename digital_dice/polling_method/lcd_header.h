#include<LPC21XX.H>
#define LCD 0xff
#define RS 1<<8
#define EN 1<<9

void delay_ms(unsigned int ms)
{
	int i;
	for(ms; ms>0; ms--)
	for(i=12000; i>=0; i--);
}


void LCD_STRING(unsigned char *);
void LCD_CMD(unsigned char);
void LCD_INIT(void);
void LCD_DATA(unsigned char);

void LCD_INIT(void)
{
	IODIR0 = LCD | RS | EN;
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
	delay_ms(2);
	IOCLR0 = EN;
}


void LCD_DATA(unsigned char d)
{
	IOPIN0 = d;
	IOSET0 = RS;
	IOSET0 = EN;
	delay_ms(2);
	IOCLR0 = EN;	
}

void LCD_STRING(unsigned char *s)
{
	while(*s)
	LCD_DATA(*s++);
}

void LCD_INT(int n)
{
	char a[5];
	int i=0;
	if(n==0)
	LCD_DATA('0');
	
	else{

		if(n<0)
		{
			LCD_DATA('-');
			n = -n;
		}

		while(n!=0)
		{
			a[i++] = n%10;
			n=n/10;
		}
		for(--i; i>=0; i--)
		LCD_DATA(a[i]+48);
	}


}				    


