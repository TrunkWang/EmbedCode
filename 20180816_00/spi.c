#include"spi.h"
#include<reg52.h>



sbit CLK = P0 ^ 4;
sbit CS = P0 ^ 5;
sbit DIN = P0 ^ 6;
sbit DOUT = P0 ^ 7;


void SPI_Enable(void )
{
	CS = 0;
}

void SPI_disable(void )
{
	CS = 1;
}

void SPI_Write(char da)
{
	int i=0;

	for(i=0;i<8;i++)
	{	
		CLK = 0;
		DIN = da >> 7;
		da = da << 1;
		delay10us();
		CLK = 1;
		delay10us();
	}
}


void SPI_Wait(void )
{
   	CLK = 0;
	delay10us();
	CLK = 1;
 	delay10us();
}


unsigned int SPI_Read(void )
{
	unsigned int red=0;
	int i=0;
	for(i=0;i<12;i++)
	{
		CLK = 0;
		delay10us();
		red = red << 1;
		red = red | DOUT;	
		CLK = 1;
		delay10us();
	}

	if(1)
	{
	CLK = 0;
	delay10us();
	CLK = 1;
	delay10us();

	CLK = 0;
	delay10us();
	CLK = 1;
	delay10us();

	CLK = 0;
	delay10us();
	CLK = 1;
	delay10us();
	CLK = 0;
	}
	return red;
}


unsigned int XPT2046_Read(void )
{
	unsigned int retdata=0;
	SPI_Enable();
	SPI_Write(0x94);
	SPI_Wait();
	retdata = 	SPI_Read();
	SPI_disable();
	return retdata;
}
