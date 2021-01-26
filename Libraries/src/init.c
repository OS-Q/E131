/*******************************************************************************
****版本：V1.0.0
****平台：STM8S003
****日期：2021-01-12
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "init.h"

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void port_init()
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

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void clk_init()
{
    disableInterrupts();
    CLK->ICKR = 0;
    CLK->ICKR |= CLK_ICKR_HSIEN;    //开启内部HSI
    // CLK_ECKR = 0;
    CLK->SWR = CLK_SWR_RESET_VALUE; //HSI为主时钟源
    CLK->CKDIVR=0x00;               //HSI不分频
    while (0 == (CLK->ICKR & CLK_ICKR_HSIRDY)); //HSI准备就绪
    CLK->PCKENR1 = 0xFF;
    CLK->PCKENR2 = 0xFF;
    CLK->CCOR = 0;
    CLK->HSITRIMR = 0;
    CLK->SWIMCCR = 0;

    CLK->SWCR = 0;
    CLK->SWCR |= CLK_SWCR_SWEN;
    while (0 != (CLK->SWCR & CLK_SWCR_SWBSY));
    enableInterrupts();
}

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void tim1_init(uint16_t Prescaler, uint16_t Period)
{
    disableInterrupts();
    TIM1->ARRH = (uint8_t)((Period-1) >> 8);
    TIM1->ARRL = (uint8_t)(Period-1);
    TIM1->PSCRH = (uint8_t)(Prescaler >> 8);
    TIM1->PSCRL = (uint8_t)(Prescaler);
    TIM1->RCR = 0;
    TIM1->SR1 = 0xFE;
    TIM1->SR2 = 0x1E;
    TIM1->IER = 0x01;
    TIM1->CR1 = 0x01;
    enableInterrupts();
}




/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
