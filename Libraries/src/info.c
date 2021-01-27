/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "info.h"



/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
uint16_t clk_freq(void)
{
    uint32_t clockfreq = 0;
    uint8_t clocksource = 0xE1;
    uint8_t tmp = 0, presc = 0;
    uint8_t HSIDivFactor[4] = {1, 2, 4, 8};
    clocksource = (uint8_t)CLK->CMSR;
    if(clocksource == 0xE1)
    {
        tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
        tmp = (uint8_t)(tmp >> 3);
        presc = HSIDivFactor[tmp];
        clockfreq = HSI_VALUE/presc;
    }
    else if(clocksource == 0xD2)
    {
        clockfreq = LSI_VALUE;
    }
    else if(clocksource == 0xB4)
    {
        clockfreq = HSE_VALUE;
    }
    return (uint16_t)(clockfreq/1000);
}




/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
