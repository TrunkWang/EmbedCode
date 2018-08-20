

#include "reg52.h"
#include "uart.h"
#include "spi.h"

#include<stdio.h>
#include<string.h>


void main()
{
	unsigned int value;
	unsigned char sendbuf[50];

	Uart_Init();

	sprintf(sendbuf,"system ready\n");
	Send_String(sendbuf,strlen(sendbuf));

	//P0=1;
	while(1)
	{
		
		value = XPT2046_Read();

		sprintf(sendbuf,"value = %d\n",value);
		Send_String(sendbuf,strlen(sendbuf));
		delay100ms();
		delay100ms();
		delay100ms();
		delay100ms();
		delay100ms();
	
	}		
}
