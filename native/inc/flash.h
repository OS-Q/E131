#ifndef __FLASH_H
#define __FLASH_H

// #include <stdint.h>

void flash_unlock(void);
void flash_lock(void);
void flash_busy_wait(void);

#endif /*__FLASH_H*/
