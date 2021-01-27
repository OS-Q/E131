#ifndef __TIMER1_H
#define __TIMER1_H

#include <stdint.h>


void tim1_stop(void);
void tim1_init(uint16_t Prescaler, uint16_t Period);
void tim1_isr(void) __interrupt(11);

#endif /*__TIMER4_H*/
