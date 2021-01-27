/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "adc.h"

void adc_init(void)
{
    /* configure ADC channel 4 (PD3)  */
    ADC1->CSR |= (1 << 2);
    ADC1->CR2 |= ADC1_CR2_ALIGN;
    ADC1->CR1 |= ADC1_CR1_ADON;
}

uint16_t adc_get(void)
{
    uint8_t adcH, adcL;
    ADC1->CR1 |= ADC1_CR1_ADON;
    while (!(ADC1->CSR & ADC1_CSR_EOC));
    adcL = ADC1->DRL;
    adcH = ADC1->DRH;
    ADC1->CSR &= ~(ADC1_CSR_EOC); // clear EOC flag
    return (adcL | (adcH << 8));
}


/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
