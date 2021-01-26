
#include "stm8s_clk.h"


void CLK_HSICmd(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CLK->ICKR |= CLK_ICKR_HSIEN;
    }
    else
    {
        CLK->ICKR &= (uint8_t)(~CLK_ICKR_HSIEN);
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
