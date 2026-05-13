#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <avr/io.h>

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(char *str);

#endif