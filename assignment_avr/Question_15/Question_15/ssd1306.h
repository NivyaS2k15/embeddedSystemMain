/*
 * ssd1306.h
 *
 * Created: 13-05-2026 15:27:15
 *  Author: NIVYA
 */ 

#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>

#define OLED_ADDR 0x3C

void ssd1306_init(void);
void ssd1306_command(uint8_t cmd);
void ssd1306_clear(void);
void ssd1306_set_cursor(uint8_t row, uint8_t col);
void ssd1306_print(char *str);

#endif