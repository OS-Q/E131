#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

#define EEPROM_START_ADDR      0x4000
#define EEPROM_END_ADDR        0x407F

#define _MEM_(mem_addr)      (*(volatile uint8_t *)(mem_addr))

/* Option bytes */
#define OPT0                   _MEM_(0x4800)
#define OPT1                   _MEM_(0x4801)
#define NOPT1                  _MEM_(0x4802)
#define OPT2                   _MEM_(0x4803)
#define NOPT2                  _MEM_(0x4804)
#define OPT3                   _MEM_(0x4805)
#define NOPT3                  _MEM_(0x4806)
#define OPT4                   _MEM_(0x4807)
#define NOPT4                  _MEM_(0x4808)
#define OPT5                   _MEM_(0x4809)
#define NOPT5                  _MEM_(0x480A)


void eeprom_unlock(void);
void eeprom_lock(void);
void option_bytes_unlock(void);
void eeprom_wait_busy(void);

#endif /* EEPROM_H */
