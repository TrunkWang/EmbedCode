
#include<reg52.h>
#include<intrins.h>
#include<stdio.h>
#include<string.h>


/*******************************************/
// define
/*******************************************/
char busy=0;
char commond='0';



/*******************************************/
// function
/*******************************************/

void Uart_Init(void );
void Send_String(char *cs,int csl);

void ExternIsr_Init(void );
int ScanKey(void );


 /*******************************************/
// main
/*******************************************/
void main(void )
{
	int i=0;
	char ledflag=0;
	char sendbuf[50];

	P0 = 0;

	ExternIsr_Init();
	Uart_Init();

	while(1)
	{
		i = ScanKey();
		if(i>0)
		{
			sprintf(sendbuf,"key value %d\n",i);
			Send_String(sendbuf,strlen(sendbuf));
		}

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

void ExternIsr_Init(void )
{
	P3 = 0xFF;
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

int ScanKey(void )
{
	int i=0;
	if(P1==0x0E)
	{
		P1 = 0xF0;
		switch(P1)
		{
			case 0x70:
			i = 4;
			break;
			case 0xB0:
			i = 8;
			break;
			case 0xD0:
			i = 12;
			break;
			case 0xE0:
			i = 16;
			break;
			default:
			break;
		}
		while(P1!=0xF0);		
	}
	else if(P1 == 0x0D)
	{
		P1 = 0xF0;
		switch(P1)
		{
			case 0x70:
			i = 3;
			break;
			case 0xB0:
			i = 7;
			break;
			case 0xD0:
			i = 11;
			break;
			case 0xE0:
			i = 15;
			break;
			default:
			break;
		}
		while(P1!=0xF0);		
	}
	else if(P1 == 0x0B)
	{

		P1 = 0xF0;
		switch(P1)
		{
			case 0x70:
			i = 2;
			break;
			case 0xB0:
			i = 6;
			break;
			case 0xD0:
			i = 10;
			break;
			case 0xE0:
			i = 14;
			break;
			default:
			break;
		}
		while(P1!=0xF0);		
	}
	else if(P1 == 0x07)
	{
		P1 = 0xF0;
		switch(P1)
		{
			case 0x70:
			i = 1;
			break;
			case 0xB0:
			i = 5;
			break;
			case 0xD0:
			i = 9;
			break;
			case 0xE0:
			i = 13;
			break;
			default:
			break;
		}
		while(P1!=0xF0);			
	}



	P1 = 0x0F;
	return i;	
}


void Extern_Isr() interrupt 0  using 1
{
	if(commond >= '9' )
	{  
		commond = '0';
	}
	else
	{
	 	commond++;
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

