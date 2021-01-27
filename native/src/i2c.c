/*******************************************************************************
****版本：V1.0.0
****平台：STM8S
****日期：2021-01-27
****作者：Qitas
****版权：OS-Q
*******************************************************************************/
#include "stm8s.h"
#include "i2c.h"

/* Interrupt handler uses this to transfer data. */
volatile i2c_cmd_p _i2c_cmd_p;
volatile uint8_t _i2c_rx_complete;
volatile uint8_t _i2c_tx_complete;
volatile uint8_t _i2c_error;

/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void i2c_init()
{
    disableInterrupts();
    /* Disable I2C */
    I2C->CR1 &= ~I2C_CR1_PE;
    I2C->FREQR = 16;
    /* Configure I2C clock */
    I2C->CCRH = 0x00;
    I2C->CCRL = 0x50;
    I2C->TRISER = 0x11;

    /* Must always be written as 1 */
    I2C->OARH |= I2C_OARH_ADDCONF;
    /* 7-bit slave address */
    I2C->OARH &= ~I2C_OARH_ADDMODE;

    /* Enable I2C interrupts */
    I2C->ITR |= (I2C_ITR_ITBUFEN|I2C_ITR_ITERREN|I2C_ITR_ITEVTEN);

    I2C->CR2 |= I2C_CR2_ACK;

    /* Configuration ready, re-enable I2C */
    I2C->CR1 |= I2C_CR1_PE;
    enableInterrupts();
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void i2c_write_cmd(i2c_cmd_t *cmd)
{
    cmd->mode = 0;
    cmd->di = 0;
    _i2c_cmd_p = cmd;
    _i2c_tx_complete = 0;
    _i2c_error = 0;
    /* Switch to master mode. */
    I2C->CR2 |= I2C_CR2_START;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
void i2c_read_cmd(i2c_cmd_t *cmd)
{
    cmd->mode = 1;
    cmd->di = 0;
    _i2c_cmd_p = cmd;
    _i2c_rx_complete = 0;
    _i2c_error = 0;
    /* Switch to master mode. */
    I2C->CR2 |= I2C_CR2_ACK;
    I2C->CR2 |= I2C_CR2_START;
}
/*******************************************************************************
**函数信息 ：
**功能描述 ：
**输入参数 ：
**输出参数 ：
*******************************************************************************/
/* I2C interrupt service routine for master receiver */
void i2c_isr(void) __interrupt(19)
{
    uint8_t r;
    if (I2C->SR1 & I2C_SR1_SB)
    {
        /* Start condition bit set */
        /* Generate start signal and start sending address */
        r = I2C->SR1;
        /* Write slave address to data register */
        I2C->DR = (_i2c_cmd_p->address << 1) | _i2c_cmd_p->mode;

        return;
    } else if (I2C->SR1 & I2C_SR1_ADDR) {
        /* Address sent, ACK received, now send data */
        r = I2C->SR1;
        r = I2C->SR3;
        if (0 == _i2c_cmd_p->mode) {
            // Write first byte of TX
            I2C->DR = _i2c_cmd_p->data[_i2c_cmd_p->di++];
        }

        return;
    }
    else if (I2C->SR1 & I2C_SR1_RXNE)
    {
        // RX buffer not empty, ready to receive next byte
        _i2c_cmd_p->data[_i2c_cmd_p->di++] = I2C->DR;
        if (_i2c_cmd_p->di + 1 == _i2c_cmd_p->size) {
            I2C->CR2 |= I2C_CR2_STOP;
            I2C->CR2 &= ~I2C_CR2_ACK;
            _i2c_rx_complete = 1;
            return;
        }
    }
    else if (I2C->SR1 & I2C_SR1_TXE)
    {
        if (_i2c_cmd_p->di == _i2c_cmd_p->size)
        {
            // TX ready, generate stop signal
            I2C->CR2 |= I2C_CR2_STOP;
            _i2c_tx_complete = 1;
            return;
        }
        // else TX buffer empty, send next byte
        I2C->DR = _i2c_cmd_p->data[_i2c_cmd_p->di++];
    }
    else if (I2C->SR2 & I2C_SR2_AF)
    {
        // No ACK Error
        _i2c_error = 1;
    }
}

/*---------------------------(C) COPYRIGHT 2021 OS-Q -------------------------*/
