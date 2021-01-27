/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "tim4.h"

void tim4_stop(void)
{
    TIM4->CR1 &= ~TIM4_CR1_CEN;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：Prescaler = 128, fMASTER = 16MHz, Counter = 125/1ms 250/2ms
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void tim4_init(uint8_t cnt)
{
    disableInterrupts();
    TIM4->PSCR = 7; //TIM4_PSCR_128 =7
    // Enable update interrupt for timer 4
    TIM4->IER |= TIM4_IER_UIE;
    // Clear timer interrupt flag
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    // 自动重装值
    TIM4->ARR  = ~(uint8_t)(cnt);
    // TIM4->CNTR = ~(uint8_t)(cnt);
    TIM4->CR1 |= TIM4_CR1_CEN;
    enableInterrupts();
}

// void tim4_isr(void) __interrupt(23)
// {
//     // Clear interrupt flag
//     TIM4->SR &= ~TIM4_SR1_UIF;
// }

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
