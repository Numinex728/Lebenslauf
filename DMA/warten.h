#ifndef WARTEN_H
#define WARTEN_H

#include "stdint.h"

void setup_tim6(void);
void setup_tim7(void);

void wait_us(void);

void tim6_wait_10us(uint16_t us);
void tim6_wait_ms(uint16_t ms);
void tim6_wait_s(uint16_t s);

void tim7_gen_us(uint16_t us);
void tim7_gen_ms(uint16_t us);
void tim7_gen_s(uint16_t s);

#endif // WARTEN_H
