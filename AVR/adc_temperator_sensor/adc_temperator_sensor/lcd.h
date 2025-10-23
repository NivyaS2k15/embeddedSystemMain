/*
 * lcd.h
 *
 * Created: 22-10-2025 17:07:03
 *  Author: NIVYA
 */ 


#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  This is our connection


// define some macros for the pins used

// for RS pin
#define LCD_RS_PORT   PORTB
#define LCD_RS_DDR    DDRB
#define LCD_RS_PIN    PB4

// for enable pin EN
#define LCD_EN_PORT   PORTB
#define LCD_EN_DDR    DDRB
#define LCD_EN_PIN    PB3

// for data/commands
#define LCD_D_PORT    PORTD
#define LCD_D_DDR     DDRD
#define LCD_D7_PIN    PD2
#define LCD_D6_PIN    PD3
#define LCD_D5_PIN    PD4
#define LCD_D4_PIN    PD5


// now lets declare  our  functions

void lcd_init(void);  					// for initialisation sequence
void lcd_cmd(uint8_t c);				// for commands(instructions
void lcd_data(uint8_t d);				// for data
void lcd_set_cursor(uint8_t row, uint8_t col);		  // for setting cursor(row: 0 or 1, col: 0..15)
void lcd_print(const char *s);				// to print string
void lcd_clear(void);					// to clear_lcd
void lcd_home(void);				// to return cursor to origin (row=0. Column =0)

void lcd_print_uint16(uint16_t v);		// to print an integer value
void lcd_print_float(float value);

#endif

