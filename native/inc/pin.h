#ifndef __PIN_H
#define __PIN_H

#include "stm8s.h"
// #include <stdint.h>
#define LED1_PORT               (GPIOB)
#define LED1_PIN                (GPIO_PIN_5)
#define LED1_ON                 (LED1_PORT->ODR &= (uint8_t)(~LED1_PIN))
#define LED1_OFF                (LED1_PORT->ODR |= (uint8_t)LED1_PIN)
#define LED1_TOG                (LED1_PORT->ODR ^= (uint8_t)LED1_PIN)


void pin_init(void);
void irq_init(void);


#endif /*__PIN_H*/
