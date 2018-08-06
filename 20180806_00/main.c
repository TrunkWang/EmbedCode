
#include<reg52.h>

sbit led = P0^0;

void main(void )
{
	P0=0;
	P1=0;

	led = 1;
	while(1)
	{
		;
	}

	return;
}