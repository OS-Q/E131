#include "stm8s.h"
#include "Modbus.h"
#include "ModbusPort.h"

// This port file for STM8S microcontrollers!

// Modbus RTU Variables
volatile unsigned char   PetitReceiveBuffer[PETITMODBUS_RECEIVE_BUFFER_SIZE];   // Buffer to collect data from hardware
volatile unsigned char   PetitReceiveCounter=0;                                 // Collected data number

// UART Initialize for Microconrollers, yes you can use another phsycal layer!
void ModBus_UART_Initialise(void)
{
    UART1_DeInit();
    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);   //UART1_IT_RXNE
    UART1_Cmd(ENABLE);             /* Enable the UART1*/  
    // UART1_DeInit();
    // UART1_Init((uint32_t)9600, \
    //            UART1_WORDLENGTH_8D, \
    //            UART1_STOPBITS_1, \
    //            UART1_PARITY_NO , \
    //            UART1_SYNCMODE_CLOCK_DISABLE , \
    //            UART1_MODE_TXRX_ENABLE);
    // UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE);
    // UART1_Cmd(ENABLE); 
}

// Timer Initialize for Petit Modbus, 1ms Timer will be good for us!
void ModBus_TIMER_Initialise(void)
{

  //TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 4095, 0);
//   TIM1_TimeBaseInit(2, TIM1_COUNTERMODE_UP, 4095, 0);
//   TIM1_CCPreloadControl(ENABLE);
//   TIM1_ITConfig(TIM1_IT_COM, ENABLE);
//   TIM1_Cmd(ENABLE);
//   TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
     
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_128, 125-1); // 1 ms
  /* Clear TIM2 update flag */
  TIM2_ClearFlag(TIM2_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE); 
  /* Enable TIM2 */
  TIM2_Cmd(ENABLE);
}

// This is used for send one character
/*
void ModBus_UART_Putch(unsigned char c)
{
    // Loop until the end of transmission
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); // wait while tx buffer will be empty
    UART1_SendData8(c);
}
*/

// This is used for send string, better to use DMA for it ;)
unsigned char ModBus_UART_String(unsigned char *s, unsigned int Length)
{
    unsigned short  DummyCounter;
    
    //Set Max485 in Transmitter mode
    // GPIO_WriteHigh(GPIOA, GPIO_PIN_3);

    for(DummyCounter=0; DummyCounter<Length; DummyCounter++)
    {
        UART1_SendData8((uint8_t)(s[DummyCounter]));
	while ((UART1->SR & UART1_SR_TXE ) != UART1_SR_TXE );

        //ModBus_UART_Putch(s[DummyCounter]);
    }
    
    //Set Max485 in Receiver mode
    // GPIO_WriteLow(GPIOA, GPIO_PIN_3);
    
    return TRUE;
}

/*************************Interrupt Fonction Slave*****************************/
// Call this function into your UART Interrupt. Collect data from it!
// Better to use DMA
void ReceiveInterrupt(unsigned char Data)
{
    PetitReceiveBuffer[PetitReceiveCounter] = Data;
    PetitReceiveCounter++;

    if(PetitReceiveCounter>PETITMODBUS_RECEIVE_BUFFER_SIZE)
        PetitReceiveCounter=0;

    ModbusTimerValue=0;
}

// Call this function into 1ms Interrupt or Event!
void ModBus_TimerValues(void)
{
    ModbusTimerValue++;
}
/******************************************************************************/
