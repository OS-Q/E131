/*******************************************************************************
****版本：V1.0.0
****平台：STM8S003
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include <stddef.h>
#include "stm8s.h"
#include "timer4.h"

volatile uint8_t *_t4_timeoutp;

/**
 * Timer 4 is a simple 8-bit upcounting counter.
 * Prescaler = 128, fMASTER = 16MHz, Counter = 125 => interrupt interval
 * is 1ms.
 */
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void timer4_init()
{
    nointerrupts();
    // CK_PSC (internal fMASTER) is divided by the prescaler value.
    TIM4_PSCR = TIM4_PSCR_128;
    // Enable update interrupt for timer 4
    TIM4_IER |= TIM4_IER_UIE;
    // Clear timer interrupt flag
    TIM4_SR &= ~TIM4_SR_UIF;
    interrupts();
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void timer4_start(uint8_t *timeoutp) {
    // Enable timer 4
    _t4_timeoutp = timeoutp;
    TIM4_CR1 |= TIM4_CR1_CEN;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void timer4_stop() {
            // disable t4
    TIM4_CR1 &= ~TIM4_CR1_CEN;
    _t4_timeoutp = NULL;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void timer4_isr(void) __interrupt(INT_TIM4)
{
    if (*_t4_timeoutp > 0) {
        (*_t4_timeoutp)--;
    } else {
        timer4_stop();
    }
    // Clear interrupt flag
    TIM4_SR &= ~TIM4_SR_UIF;
    // Rewrite counter, calculated value is 125
    TIM4_CNTR = 0xFF - 128;
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
