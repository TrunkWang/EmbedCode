
#include<reg52.h>
#include<intrins.h>


void delay100ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}


void main(void )
{
	int i = 0;
	P0=0;
	while(1)
	{
		P0 = 0;
		for(i=0;i<8;i++)
		{
			delay100ms();
			P0 |= 0x01 << i;
		}
		
		for(i=0;i<8;i++)
		{
			delay100ms();
			P0 = P0 >> i;
		}
	}
	return;
}

