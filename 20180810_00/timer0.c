

#include<reg52.h>
#include"timer0.h"


void timer0_Init(void )
{
	EA = 0;			//�ر����ж�

	TMOD = TMOD | 0x01;		//��ʱ��0������ģʽ1������16λ����
	TH0 =0xD8;				//ͨ��С���߼���õ�   10ms:0xD8F0
	TL0 =0xF0;				//ͨ��С���߼���õ�   10ms:0xD8F0
	TR0 = 1;				//������ʱ����ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�

	EA = 1;			//�����ж�
}

void Timer0_Isr() interrupt 1
{


}


