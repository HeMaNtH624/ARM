#include<LPC21XX.H>
#define RAM_ADDR 0x40000000
int main()
{
	unsigned int temp = 0;
	 unsigned int *ptr = (unsigned int*)RAM_ADDR;
	while(1)
	{
	temp = *ptr;
	if(temp)
	break;
	}
	while(1);
}