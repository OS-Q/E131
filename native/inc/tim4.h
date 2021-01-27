#ifndef __TIMER4_H
#define __TIMER4_H

#include <stdint.h>


void tim4_init(uint8_t cnt);
void tim4_stop(void);
void tim4_isr(void) __interrupt(23);

#endif /*__TIMER4_H*/
