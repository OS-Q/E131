#ifndef __UART1_H
#define __UART1_H

#include <stdint.h>

void uart1_init(uint8_t buad,uint8_t pair);
uint8_t uart1_put(const char *s);
uint8_t uart1_get(void);
void uart1_set(uint8_t data);

// void uart1_isr(void) __interrupt(18);

#endif /* __UART1_H */
