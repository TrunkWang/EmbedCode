
#include<reg52.h>

#include<stdio.h>
#include<string.h>

#include"delay.h"
#include"uart.h"
#include"iic.h"

/*******************************************/
// define
/*******************************************/


/*******************************************/
// function
/*******************************************/


 /*******************************************/
// main
/*******************************************/
void main(void )
{
	int i=0;
	unsigned char sendbuf[50];
	unsigned char rbyte;	

	Uart_Init();
	sprintf(sendbuf,"system ready\n");
	Send_String(sendbuf,strlen(sendbuf));
	
	
	AT24C02_SendByte(1,0x0A);
	delay1ms();
	rbyte = AT24C02_ReadByte(1);
	i = rbyte;

	sprintf(sendbuf,"iic read data %d\n",i);
	Send_String(sendbuf,strlen(sendbuf));


	while(1)
	{
			
	}
}

