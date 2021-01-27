#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>

/*
 * Initialize SPI in MODE1.
 * Pinout:
 * SCK  -> PC5
 * MOSI -> PC6
 * MISO -> PC7
 * CS   ->
 */

void spi_init(void);
void spi_set(uint8_t data);
uint8_t spi_get(void);

#endif /* SPI_H */

