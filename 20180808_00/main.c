
#include<reg52.h>
#include<intrins.h>
#include<stdio.h>
#include<string.h>


/*******************************************/
// define
/*******************************************/
char busy=0;
char commond=0;



/*******************************************/
// function
/*******************************************/

void delay1s(void);
void Uart_Init(void );
void Send_String(char *cs,int csl);

 /*******************************************/
// main
/*******************************************/
void main(void )
{
	int i=0;
	char ledflag=0;
	char sendbuf[50];

	P0 = 0;
	Uart_Init();

	while(1)
	{
		if(ledflag != commond)
		{
			ledflag =  commond;
			if((ledflag >= '0')&&(ledflag <= '9'))
			{
				if((ledflag - '0') == 0)
				{
					sprintf(sendbuf,"led all off\n");
					P0=0;
				}
				else if ((ledflag - '0') ==9)
				{
					sprintf(sendbuf,"led all on\n");
					P0=0xFF;
				}
				else
				{	
					i =   (ledflag - '0');
					sprintf(sendbuf,"led %d on\n",i);
					P0= 0x01 << (ledflag - '0')-1;
				}
			}
			else
			{
				sprintf(sendbuf,"commond error please check\n");
			}
			Send_String(sendbuf,strlen(sendbuf));
		}
	}
}


void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void Uart_Init(void )
{
	SM0   = 0;
	SM1   = 1;
	SM2   = 0;
	REN   = 1;
	TB8   = 0;
	RB8   = 0;
	TI    = 0;
	RI    = 0;

	PCON = 0x80;

	TMOD = 0x20;
	TH1=TL1=0xf3;
	TR1= 1;


	ES = 1;
	EA = 1;

	busy = 0;

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



void Uart_Isr() interrupt 4 using 1
{
	if(RI)
	{
		RI = 0;
		commond = SBUF;
	}
	if(TI)
	{
		busy = 0;
		TI=0;
	}
}

