/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "eeprom.h"

#define FLASH_DUKR_KEY1         0xAE
#define FLASH_DUKR_KEY2         0x56

void eeprom_unlock(void)
{
    FLASH->DUKR = FLASH_DUKR_KEY1;
    FLASH->DUKR = FLASH_DUKR_KEY2;
    while (!(FLASH->IAPSR & FLASH_IAPSR_DUL));
}

void eeprom_lock(void)
{
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
}

void option_bytes_unlock(void)
{
    FLASH->CR2 |= FLASH_CR2_OPT;
    FLASH->NCR2 &= ~FLASH_NCR2_NOPT;
}
void eeprom_wait_busy(void)
{
    while (!(FLASH->IAPSR & FLASH_IAPSR_EOP));
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
