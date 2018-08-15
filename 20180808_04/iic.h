#ifndef _IIC_H_
#define _IIC_H_

void AT24C02_SendByte(unsigned char addr,unsigned char dabyte);

unsigned char AT24C02_ReadByte(unsigned char addr);


#endif

