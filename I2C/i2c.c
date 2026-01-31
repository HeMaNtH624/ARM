#include<LPC21XX.H>
#include "lcd_header.h"

#define SCL 0x00000010
#define SDA 0X00000040
#define SEN 6
#define STA 5
#define STO 4
#define SI 3
#define aack 2

typedef unsigned char u8;

void eeprom_write(u8 slv_addr, u8 data_addr, u8 data);
u8 eeprom_read( u8 slv_addr, u8 data_addr);

void i2c_write(u8 ch);
u8 i2c_read(void);

void start(void);
void stop(void);
void restart(void);
void i2c_init(void);

void eeprom_write(u8 slv_addr, u8 data_addr, u8 data)
{
	start();
	i2c_write(slv_addr<<1);
	i2c_write(data_addr);
	i2c_write(data);
	stop();
	delay_ms(10);
}

u8 eeprom_read( u8 slv_addr, u8 data_addr)
{
	u8 ch;
	start();
	i2c_write(slv_addr<<1);
	i2c_write(data_addr);
	restart();
	i2c_write((slv_addr<<1)|1);
	ch=i2c_read();
	stop();
	return ch;
}

void i2c_write(u8 ch)
{
	I2DAT=ch;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
}

u8 i2c_read(void)
{
	I2CONSET=0X00;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	return I2DAT;
}

void start(void)
{
	I2CONSET=1<<STA;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}

void stop(void)
{
	I2CONSET=1<<STO;
	I2CONCLR=1<<SI;
}

void restart(void)
{
	I2CONSET=1<<STA;
	I2CONCLR=1<<SI;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STA;
}

void i2c_init(void)
{
	PINSEL0|=SCL|SDA;
	I2SCLH=75;
	I2SCLL=75;
	I2CONSET=1<<SEN;
}

int main()
{
	char ch;
	i2c_init();
	LCD_INIT();
	LCD_CMD(0X80);
	LCD_STRING("I2C TESTING");
	IODIR0|=1<<7|1<<8;
	eeprom_write(0x50, 0x00, 'A');
	ch=eeprom_read(0x50, 0x00);
	LCD_CMD(0XC0);
	LCD_DATA(ch);
}
