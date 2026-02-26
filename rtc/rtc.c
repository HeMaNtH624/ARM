#include<lpc21xx.h>
#include "lcd_header.h"
#define IEN 6
#define STA 5
#define STO 4
#define SI 3
#define AAC 2


typedef unsigned char u8;

void byte_write(u8 ch);
u8 byte_read(void);
void eeprom_write(u8 slv_addr, u8 data_addr, u8 data);
u8 eeprom_read(u8 slv_addr, u8 data_addr);
void eeprom_page_write(u8 slv_addr, u8 data_addr, u8 *data, u8 size);
u8 *eeprom_page_read(u8 slv_addr, u8 data_addr, u8 size);

void i2c_init()
{
	PINSEL0|=0X00000050;
	I2SCLH=75;
	I2SCLL=75;
	I2CONSET|=1<<IEN;
}

void start()
{
	I2CONSET|=1<<STA;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR|=1<<STO;
}

void stop()
{
	I2CONSET=1<<STO;
	I2CONCLR=1<<SI;
}

void restart(void)
{
	I2CONSET=1<<STA;
	I2CONCLR=1<<SI;
	while(((I2CONSET<<SI)&1)==0);
	I2CONCLR=1<<STA;
}

u8 master_ack(void)
{
	I2CONSET=1<<AAC;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<AAC;
	return I2DAT;
}

void byte_write(u8 ch)
{
	I2DAT=ch;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
}

u8 byte_read(void)
{
	I2CONSET=0X00;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);	
	return I2DAT;
}

void eeprom_write(u8 slv_addr, u8 data_addr, u8 data)
{
	start();
	byte_write(slv_addr<<1);
	byte_write(data_addr);
	byte_write(data);
	stop();
	delay_ms(10);
}

u8 eeprom_read(u8 slv_addr, u8 data_addr)
{
	u8 ch;
	start();
	byte_write(slv_addr<<1);
	byte_write(data_addr);
	restart();
	byte_write(slv_addr<<1|1);
	ch=byte_read();
	stop();
	return ch;
}

void eeprom_page_write(u8 slv_addr, u8 data_addr, u8 *data, u8 size)
{
	u8 i;
	start();
	byte_write(slv_addr<<1);
	byte_write(data_addr);
	for(i=0; i<size; i++)
	{
		I2DAT=data[i];
	}
	stop();
	delay_ms(10);
}

u8 *eeprom_page_read(u8 slv_addr, u8 data_addr, u8 size)
{
	u8 *data, i;
	start();
	byte_write(slv_addr<<1);
	byte_write(data_addr);
	restart();
	for(i=0; i<size-1; i++)
	{
		data[i]=master_ack();
	}
	data[i]=byte_read();
	stop();
	return data;
}

void rtc_write(u8 slv_addr, u8 data_addr)
{
	
}

U8 *rtc_read(u8 slv_addr, u8 data_addr)
{
	
}

int main()
{
	unsigned char ch;
	LCD_INIT();
	i2c_init();
	LCD_CMD(0X80);
	LCD_STRING("REAL TIME CLOCK:");
	IODIR0|=1<<6|1<<7;
	IOSET0|=1<<6|1<<7;

	eeprom_page_write(0x50, 0x00, "HEMANTH", 7);
}
