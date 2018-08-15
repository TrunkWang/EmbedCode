
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
	SM0   = 0;		//���ڷ�ʽ1 SM0:0 SM1:1
	SM1   = 1;		//���ڷ�ʽ1 SM0:0 SM1:1
	SM2   = 0;
	REN   = 1;	 	//������տ���
	TB8   = 0;
	RB8   = 0;
	TI    = 0;		//����8bit������Ӳ����1���жϴ��������ж����������
	RI    = 0;		//����8bit������Ӳ����1���жϴ��������ж����������

	PCON = 0x80;	//�����ʼӱ� SMOD

	TMOD = 0x20;	//Timer1 ������ʱ����8λ�Զ���װ��		
	TH1=TL1=0xf3;	//ͨ��С�������õ�  4800:0xf3
	TR1= 1;	 		//������ʱ

#ifdef ENABLE_TIMER0
	TMOD = TMOD | 0x01;		//��ʱ��0������ģʽ1������16λ����
	TH0 =0xD8;				//ͨ��С���߼���õ�   10ms:0xD8F0
	TL0 =0xF0;				//ͨ��С���߼���õ�   10ms:0xD8F0
	TR0 = 1;				//������ʱ����ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
#endif

	ES = 1;			//�򿪴����ж�

	EA = 1;			//�����ж�

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




