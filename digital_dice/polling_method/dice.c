#include<LPC21XX.H>
#define sw 10

#define LCD 0XFF
#define RS 1<<8
#define EN 1<<9

void LCD_STRING(unsigned char *);
void LCD_CMD(unsigned char);
void LCD_INIT(void);
void LCD_DATA(unsigned char);
void LCD_INT(int );

void delay_ms(int n)
{
	T1PR = 15000-1;
	T1TCR = 0X01;
	while(T1TC<n);
	T1TCR = 0X03;
	T1TCR = 0X00;
}

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

unsigned char arr[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
					   0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00,
					   0x00, 0x03, 0x03, 0x00, 0x00, 0x18, 0x18, 0x00,
					   0x00, 0x1b, 0x1b, 0x00, 0x04, 0x04, 0x00, 0x00,
					   0x00, 0x1b, 0x1b, 0x00, 0x00, 0x1b, 0x1b, 0x00,
					   0x00, 0x1b, 0x1b, 0x04, 0x04, 0x1b, 0x1b, 0x00,
					   0x1b, 0x1b, 0x00, 0x1b, 0x1b, 0x00, 0x1b, 0x1b
					   };
void cg_ram(int n)
{
	int i;
	LCD_CMD(0X40);
	for(i=0; i<n; i++)
	LCD_DATA(arr[i]);


}

int main()
{
	//unsigned int i, j, k, n;
	T0PR = 5;
	T0TCR = 0X01;
	LCD_INIT();
	cg_ram(56);
	LCD_CMD(0X80);
	LCD_STRING("~ DIGITAL DICE ~");	
	while(1)
	{  

		if(((IOPIN0>>sw)&1)==0)	 	
		{
			while(((IOPIN0>>sw)&1)==0);
			delay_ms(250);
			T0TCR = 0x00; 

			LCD_CMD(0XC2);
			LCD_DATA(T0PC+1);
			
			LCD_CMD(0XC4);
			LCD_INT(T0PC+1);
			
		}
		else 
		{
			T0TCR = 0X01;
		}
	}
}