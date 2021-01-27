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

void tim4_init(void)
{
    disableInterrupts();
    // CK_PSC (internal fMASTER) TIM4_PSCR_128 =7
    TIM4->PSCR = 7;
    // Enable update interrupt for timer 4
    TIM4->IER |= TIM4_IER_UIE;
    // Clear timer interrupt flag
    TIM4->SR1 &= ~TIM4_SR1_UIF;
    TIM4->ARR  = 0xFF - 125;
    TIM4->CNTR = 0xFF - 125;
    TIM4->CR1 |= TIM4_CR1_CEN;
    enableInterrupts();
}

// void tim4_isr(void) __interrupt(23)
// {
//     // Clear interrupt flag
//     TIM4->SR &= ~TIM4_SR1_UIF;
// }

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
