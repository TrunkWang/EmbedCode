
#include<reg52.h>
#include"iic.h"
#include"delay.h"

/*******************************************/
// define
/*******************************************/

sbit SCL = P2 ^ 1;
sbit SDA = P2 ^ 0;			    

/*******************************************/
// define
/*******************************************/


void IIC_Start(void )
{
	SDA = 1;
	delay10us();
	SCL = 1;
	delay10us();
	SDA = 0;
	delay10us();
	SCL = 0;
	delay10us();
}

void IIC_Stop(void )
{
	SDA = 0;
	delay10us();
	SCL = 1;
	delay10us();
	SDA = 1;
	delay10us();
}


int IIC_SendByte(unsigned char daByte)
{
	int i=0,ret=1;
	
	for(i=0;i<8;i++)
	{
		SDA = daByte >> 7;
		daByte = daByte << 1;
		delay10us();
		SCL = 1;
		delay10us();
		SCL = 0;
		delay10us();
	}

	SDA = 1;
	delay10us();
	SCL = 1;
	delay10us();
	
	i = 0;
	while(SDA)
	{
		i++;
		if(i>200)
		{
			ret = 0;
			break;
		}
		
	}
	SCL = 0;
	delay10us();

	return ret;
}


unsigned char IIC_ReadByte(void )
{
	unsigned char ret;
	int i=0;

	for(i=0;i<8;i++)
	{
		SCL = 1;
		delay10us();
		ret = ret << 1;
		ret = ret | SDA;
		SCL = 0;
		delay10us();		
	}

	return ret;
}


void AT24C02_SendByte(unsigned char addr,unsigned char dabyte)
{
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_SendByte(addr);
	IIC_SendByte(dabyte);
	IIC_Stop();
}


unsigned char AT24C02_ReadByte(unsigned char addr)
{
	unsigned char ret;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_SendByte(addr);
	IIC_Start();
	IIC_SendByte(0xa1);
	ret = IIC_ReadByte();
	IIC_Stop();
	return ret;
}

