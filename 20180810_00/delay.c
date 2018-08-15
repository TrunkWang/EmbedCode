

#include"delay.h"
#include<intrins.h>


void delay10us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=2;a>0;a--);
}

void delay50us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=22;a>0;a--);
}


void delay100us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=47;a>0;a--);
}

void delay500us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=71;b>0;b--)
        for(a=2;a>0;a--);
}


void delay1ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}


void delay10ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}


void delay50ms(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=173;b>0;b--)
        for(a=143;a>0;a--);
}


void delay100ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}


void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
