/*
 * lcd.h
 *
 *  Created on: Dec 26, 2025
 *      Author: NIVYA
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"
#include <stdint.h>

/*
 * LCD PIN CONNECTIONS (Updated)
 * RS  -> PC0
 * EN  -> PC1
 * D4  -> PB0
 * D5  -> PA4
 * D6  -> PA1
 * D7  -> PA0
 */

#define LCD_RS_PIN      GPIO_PIN_NO_0
#define LCD_EN_PIN      GPIO_PIN_NO_1
#define LCD_D4_PIN      GPIO_PIN_NO_0
#define LCD_D5_PIN      GPIO_PIN_NO_4
#define LCD_D6_PIN      GPIO_PIN_NO_1
#define LCD_D7_PIN      GPIO_PIN_NO_0

#define LCD_RS_PORT     GPIOC
#define LCD_EN_PORT     GPIOC
#define LCD_D4_PORT     GPIOB
#define LCD_D5_PORT     GPIOA
#define LCD_D6_PORT     GPIOA
#define LCD_D7_PORT     GPIOA

// -------- LCD APIs --------
void lcd_init(void);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);
void lcd_print_uint16(uint16_t value);

#endif /* LCD_H_ */
