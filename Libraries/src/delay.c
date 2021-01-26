
#include "delay.h"

void delay_us(uint16_t nCount)
{
    while(nCount--)
    {
        nop();
        nop();
        nop();
        nop();
    }
}

void delay_ms(uint16_t nCount)
{
    while(nCount--)
    {
        delay_us(999);
    }
}

