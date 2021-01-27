#ifndef __UART_H
#define __UART_H

#include <stdint.h>

void uart_init();
uint8_t uart_puts(const char *s);


#endif /* __UART_H */
