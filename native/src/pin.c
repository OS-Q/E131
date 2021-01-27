/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "pin.h"


void pin_init(void)
{
    GPIOA->ODR = 0x00;
    GPIOA->DDR = 0xFF;
    GPIOA->CR1 = 0xFF;
    GPIOA->CR2 = 0x00;

    GPIOB->ODR = 0x00;
    GPIOB->DDR = 0xFF;
    GPIOB->CR1 = 0xCF;
    GPIOB->CR2 = 0x00;

    GPIOC->ODR = 0x00;
    GPIOC->DDR = 0xFF;
    GPIOC->CR1 = 0xFF;
    GPIOC->CR2 = 0x00;

    GPIOD->ODR = 0x00;
    GPIOD->DDR = 0xFF;
    GPIOD->CR1 = 0xFF;
    GPIOD->CR2 = 0x00;
}

void irq_init(void)
{
    EXTI->CR1 &= (uint8_t)(0x3F);
    EXTI->CR1 |= (uint8_t)((0x02)<<6);
}

// void pin_isr(void) __interrupt(6)
// {
//     // Clear interrupt flag
//     UART1->SR = 0xDF;
// }

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
