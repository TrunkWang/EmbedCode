

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器




sbit PWM=P2^1;




/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/



void main()
{
	int j=2;
	int i=20-j;
	int q=0;
	int m=0;

	int s=0;

	while(1)
	{
		m++;
		if(m==5)
		{
			m=0;
			if(s==0){j++;}else{j--;}
			if(j==0){s=0;}if(j==21){s=1;}

			i=20-j;
		}

		PWM = 1;
		for(q=0;q<j;q++)delay1ms();
		PWM = 0;
		for(q=0;q<i;q++)delay1ms();
			
	}		
}


