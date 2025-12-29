#include "lcd_header.h"
#include<string.h>

#define led1 1<<23
#define buz 1<<24
#define motor 1<<25

void UART_CONFIG(void);
unsigned char UART_RX(void);

int main()
{
	unsigned char i=0;
	char s[20];
	char ledon[10]="led on";
	char ledoff[10]="led off";
	char buzon[15]="buzzer on";
	char buzoff[15]="buzzer off";
	char moton[15]="motor on";
	char motoff[15]="motor off";
	unsigned char rxByte;
	LCD_INIT();
	LCD_CMD(0X80);
	STRING("HOME AUTOMATION"); 
	IODIR1|=led1|buz|motor;
	PINSEL0|=0X05;
	UART_CONFIG();
	IOSET1=led1|buz;
	//IOCLR1=buz|motor;
	while(1)
	{
		i=0;
		while(1)
		{
			rxByte=UART_RX();
			if(rxByte=='\r' || rxByte=='\n')
			{
				s[i]='\0';
				break;
			}
			else
				s[i++]=rxByte;
		}
		
		if((strcmp(s,ledon))==0)
		{
			IOCLR1=led1;
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			STRING("HOME-AUTOMATION");
			LCD_CMD(0XC3);
			STRING("LED IS ON");
		}
		else if((strcmp(s,ledoff))==0)
		{
			IOSET1=led1;
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			STRING("HOME-AUTOMATION");
			LCD_CMD(0XC3);
			STRING("LED IS OFF");
		}

		else if((strcmp(s,buzoff))==0)
		{
			IOSET1=buz;
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			STRING("HOME-AUTOMATION");
			LCD_CMD(0XC3);
			STRING("BUZZER OFF");
		}

		else if((strcmp(s,buzon))==0)
		{
			IOCLR1=buz;
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			STRING("HOME-AUTOMATION");
			LCD_CMD(0XC3);
			STRING("BUZZER ON");
		}

		else if((strcmp(s,moton))==0)
		{
			IOSET1=motor;
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			STRING("HOME-AUTOMATION");
			LCD_CMD(0XC3);
			STRING("MOTOR ON");
		}

		else if((strcmp(s,motoff))==0)
		{
			IOCLR1=motor;
			LCD_CMD(0X01);
			LCD_CMD(0X80);
			STRING("HOME-AUTOMATION");
			LCD_CMD(0XC3);
			STRING("MOTOR OFF");
		}
	}
}

void UART_CONFIG(void)
{
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}

unsigned char UART_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
