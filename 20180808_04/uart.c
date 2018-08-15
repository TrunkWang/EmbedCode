
#include<reg52.h>
#include"uart.h"

 /*******************************************/
// define
/*******************************************/

#define REV_BF_SIZE	(20)


/*******************************************/
// define
/*******************************************/
char busy=0;
unsigned char rbuf_pos=0x0F;
unsigned char rbuf[REV_BF_SIZE];




void Uart_Init(void )
{
	SM0   = 0;		//串口方式1 SM0:0 SM1:1
	SM1   = 1;		//串口方式1 SM0:0 SM1:1
	SM2   = 0;
	REN   = 1;	 	//允许接收控制
	TB8   = 0;
	RB8   = 0;
	TI    = 0;		//发送8bit结束后，硬件置1，中断触发，在中断中软件清零
	RI    = 0;		//接收8bit结束后，硬件置1，中断触发，在中断中软件清零

	PCON = 0x80;	//波特率加倍 SMOD

	TMOD = 0x20;	//Timer1 用作定时器，8位自动重装载		
	TH1=TL1=0xf3;	//通过小软件计算得到  4800:0xf3
	TR1= 1;	 		//启动定时

#ifdef ENABLE_TIMER0
	TMOD = TMOD | 0x01;		//定时器0，用作模式1，进行16位计数
	TH0 =0xD8;				//通过小工具计算得到   10ms:0xD8F0
	TL0 =0xF0;				//通过小工具计算得到   10ms:0xD8F0
	TR0 = 1;				//启动定时器开始计时
	ET0 = 1;				//使能定时器0中断
#endif

	ES = 1;			//打开串口中断

	EA = 1;			//打开总中断

	busy = 0;
	rbuf_pos = 0;
}


void Send_String(char *cs,int csl)
{
	int i=0;
	for(i=0;i<csl;i++)
	{
		while(busy);
		SBUF = cs[i];
		busy = 1;
	}
}

void Uart_Isr() interrupt 4
{
	if(RI)
	{
		RI = 0;
		rbuf[rbuf_pos] = SBUF;
		rbuf_pos++;
		rbuf_pos = rbuf_pos & 0x0F;
	}
	if(TI)
	{
		busy = 0;
		TI=0;
	}
}


#ifdef ENABLE_TIMER0
void Timer0_Isr() interrupt 1
{	
	int i=0;
	TH0 = 0xD8;
	TL0 = 0xF0;
	i++;
}
#endif




