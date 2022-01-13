#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"

void i2c_init( bool fastMode, uint32_t apb1_clock);
int i2c_writeByte(uint8_t slave_addr, uint8_t reg_addr, uint8_t value);

#endif // __I2C_H
