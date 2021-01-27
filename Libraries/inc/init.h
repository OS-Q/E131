#ifndef __INIT_H
#define __INIT_H


void pin_init(void);
void dog_init(void);
void clk_init(void);
void tim1_init(uint16_t Prescaler, uint16_t Period);
void reboot(void);
void feed_dog(void);
void tim1_isr(void) __interrupt(11);

#endif /*__INIT_H*/
