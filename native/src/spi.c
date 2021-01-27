/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "spi.h"

void spi_init(void)
{
    // SPI->CR1 = (1 << SPI_CR1_MSTR) | (1 << SPI_CR1_SPE) | (1 << SPI_CR1_BR1);
    // SPI->CR2 = (1 << SPI_CR2_SSM) | (1 << SPI_CR2_SSI) | (1 << SPI_CR2_BDM) | (1 << SPI_CR2_BDOE);
    SPI->CR1 = (1 << 2) | (1 << 6) | (1 << 4);
    SPI->CR2 = (1 << 1) | (1 << 0) | (1 << 7) | (1 << 6);
}

void spi_set(uint8_t data)
{
    SPI->DR = data;
    while (!(SPI->SR & (1 << 0)));
}

uint8_t spi_get(void)
{
    spi_set(0xFF);
    while (!(SPI->SR & (1 << 0)));
    return SPI->DR;
}



/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
