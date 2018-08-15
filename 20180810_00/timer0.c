

#include<reg52.h>
#include"timer0.h"


void timer0_Init(void )
{
	EA = 0;			//关闭总中断

	TMOD = TMOD | 0x01;		//定时器0，用作模式1，进行16位计数
	TH0 =0xD8;				//通过小工具计算得到   10ms:0xD8F0
	TL0 =0xF0;				//通过小工具计算得到   10ms:0xD8F0
	TR0 = 1;				//启动定时器开始计时
	ET0 = 1;				//使能定时器0中断

	EA = 1;			//打开总中断
}

void Timer0_Isr() interrupt 1
{


}


