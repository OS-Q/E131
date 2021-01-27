/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "flash.h"

/* Use last 64 bytes of flash for user data */
// #define ID_ADDR                 (0x8000 + 0x1FC0)
// #define USER_DATA_ADDR          (ID_ADDR + 1)

#define FLASH_PUKR_KEY1         0x56
#define FLASH_PUKR_KEY2         0xAE


void flash_unlock(void)
{
    FLASH->PUKR = FLASH_PUKR_KEY1;
    FLASH->PUKR = FLASH_PUKR_KEY2;
    while (!(FLASH->IAPSR & FLASH_IAPSR_PUL));
}


void flash_lock(void)
{
    FLASH->IAPSR &= ~FLASH_IAPSR_PUL;
}


void flash_busy_wait(void)
{
    while (!(FLASH->IAPSR & FLASH_IAPSR_EOP));
}



/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
