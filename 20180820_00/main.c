

#include "reg52.h"
#include "uart.h"


#include<stdio.h>
#include<string.h>

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;


unsigned char IrValue[6];
unsigned int gcount = 0;
u8 Time;

sbit IRIN = P3 ^ 2;

void main()
{
	unsigned int value;
	unsigned char sendbuf[50];

	IT0 = 1;//�½��ش���
	EX0 = 1;
	EA =  1;



	Uart_Init();

	sprintf(sendbuf,"system ready\n");
	Send_String(sendbuf,strlen(sendbuf));


	while(1)
	{
		sprintf(sendbuf,"---get count %d [%d %d %d %d ]\n",gcount,(int)IrValue[0],(int)IrValue[1],(int)IrValue[2],(int)IrValue[3]);
		Send_String(sendbuf,strlen(sendbuf));
		delay1s();
	}		
}

void delay(u16 i)
{
	while(i--);	
}



void Int0_Routine(void ) interrupt 0
{
	u8 j,k;
	u16 err;
	Time=0;					 
	delay(700);	//7ms
	if(IRIN==0)		//ȷ���Ƿ���Ľ��յ���ȷ���ź�
	{	 
		
		err=1000;				//1000*10us=10ms,����˵�����յ�������ź�
		/*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó�������ʱ
		�������������*/	
		while((IRIN==0)&&(err>0))	//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ  		
		{			
			delay(1);
			err--;
		} 
		if(IRIN==1)			//�����ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)		//����4������
			{				
				for(j=0;j<8;j++)	//����һ������
				{

					err=60;		
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
						delay(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //����ߵ�ƽ��ʱ�䳤�ȡ�
					{
						delay(10);	 //0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 //k��ʾ�ڼ�������
					if(Time>=8)			//����ߵ�ƽ���ִ���565us����ô��1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//����ʱ��Ҫ���¸�ֵ							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}
}



