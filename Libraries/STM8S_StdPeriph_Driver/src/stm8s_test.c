
#include "stm8s_test.h"


void delay_ms(uint16_t nCount)
{
    uint16_t i=0;
    while(nCount--)
    {
        for(i=0;i<1000;i++);
    }
}

