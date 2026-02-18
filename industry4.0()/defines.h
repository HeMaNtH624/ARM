/**devices**/

#define fan 1<<18
#define light 1<<19
#define buzzer 1<<20
#define conveyor 1<<21
#define led 1<<16

/***spi***/

typedef unsigned char u8;
#define CS 7
#define MSTR 5
#define LSBF 6
#define SPIE 7 

#define mode0 0x00
#define mode1 0x08
#define mode2 0x10
#define mode3 0x18

float adc_mcp(u8 ch_no);
u8 spi_wr(u8 ch);
void spi_init(void);


/***UART***/

void UART_CONFIG(void);
void UART_TX(unsigned char ch);
unsigned char UART_RX(void);
void UART_STR(unsigned char *s);


