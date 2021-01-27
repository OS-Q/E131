#ifndef __TIMER4_H
#define __TIMER4_H

#include <stdint.h>

/**
 * Timer 4 is a simple 8-bit upcounting counter.
 * Prescaler = 128, fMASTER = 16MHz, Counter = 125 => interrupt interval
 * is 1ms.
 */

void tim4_init(void);
void tim4_stop(void);
void tim4_isr(void) __interrupt(23);

#endif /*__TIMER4_H*/
