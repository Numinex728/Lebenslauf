#ifndef __LCD_I2C_H
#define __LCD_I2C_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"

#define SLAVE_ADDR 0x27
#define SPALTEN 16
#define ZEILEN 2

#define LCD_DELAY_INIT			100000  
#define LCD_DELAY_20000	     20000  
#define LCD_DELAY_500				   500    


void LCD_init(void);
void LCD_Clear(void);
void LCD_String( uint8_t x, uint8_t y, char *ptr);
void LCD_clock( uint8_t wert);
void LCD_sendCmd(uint8_t wert);
void LCD_data( uint8_t wert);
void LCD_setCursor( uint8_t x, uint8_t y);
void LCD_wait(volatile uint32_t nCount);

#endif // __LCD_I2C_H
