#include <lpc21xx.h>

//void FIQ_Handler(void) __attribute__((interrupt("FIQ")));

void fiq_intr(void) __irq
{
    EXTINT = 1;          

    IOSET0 = 1<<0;     
    IOCLR0 = 1<<0;
}

int main()
{
    unsigned int count = 0;
    IODIR0 = 1<<0;      

    PINSEL1 = 0x01;

    VICIntSelect = (1<<14); 

    EXTMODE = 0x00;   
    EXTPOLAR = 0x00;  

    VICDefVectAddr = (unsigned long)fiq_intr;
    
    VICIntEnable = (1<<14);  

    while(1)
    {
        count++;
    }
}
