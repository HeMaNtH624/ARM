#include<lpc21xx.h>
#include "defines.h"
#include "spi.h"
#include "uart.h"
#include "lcd_header.h"

int main()

{
	unsigned char rxByte;
	volatile float temp,f;
	char s[10];
	spi_init();
	UART_CONFIG();
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STRING("Industry 4.0");
	delay_ms(1000);
	IODIR0|=fan|light|buzzer|conveyor|led;
	IOSET0|=fan|light|buzzer|conveyor|led;
	
	while(1)
	{
		LCD_CMD(0x80);
		LCD_STRING("Temperature: ");
		f=adc_mcp(0);
		temp=f/0.01;
		LCD_CMD(0XC0);
		LCD_float(temp);

		if(temp>20.0)
		{
			IOCLR0|=led;
		}

		else
		{
			IOSET0|=led;
		}

		rxByte=UART_RX();
		switch(rxByte)
		{
			case 'A': 
				IOCLR0|=fan;
				break;

			case 'a':
				IOSET0|=fan;
				break;
			
			case 'B':
				IOCLR0|=light;
				break;

			case 'b':
				IOSET0|=light;
				break;

			case 'C':
				IOCLR0|=buzzer;
				break;

			case 'c':
				IOSET0|=buzzer;
				break;

			case 'D':
				IOCLR0|=conveyor;
				break;

			case 'd':
				 IOSET0|=conveyor;
				 break;
		}
	}

}
