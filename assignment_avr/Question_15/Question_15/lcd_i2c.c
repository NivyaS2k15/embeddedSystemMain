#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "lcd_i2c.h"

#define LCD_ADDR 0x27   // change to 0x3F if needed

#define RS 0x01
#define EN 0x04
#define BL 0x08

static void lcd_toggle(uint8_t data)
{
	i2c_write(data | EN);
	_delay_us(1);
	i2c_write(data & ~EN);
	_delay_us(50);
}

static void lcd_send(uint8_t value, uint8_t mode)
{
	uint8_t high = (value & 0xF0) | mode | BL;
	uint8_t low  = ((value << 4) & 0xF0) | mode | BL;

	i2c_start();
	i2c_write(LCD_ADDR << 1);

	i2c_write(high);
	lcd_toggle(high);

	i2c_write(low);
	lcd_toggle(low);

	i2c_stop();
}

static void lcd_cmd(uint8_t cmd)
{
	lcd_send(cmd, 0);
	_delay_ms(2);
}

void lcd_init(void)
{
	_delay_ms(50);

	// ?? Correct initialization sequence
	lcd_send(0x03 << 4, 0);
	_delay_ms(5);
	lcd_send(0x03 << 4, 0);
	_delay_ms(5);
	lcd_send(0x03 << 4, 0);
	_delay_ms(5);
	lcd_send(0x02 << 4, 0); // 4-bit mode

	lcd_cmd(0x28); // 2 line
	lcd_cmd(0x0C); // display ON
	lcd_cmd(0x06); // entry mode
	lcd_cmd(0x01); // clear
	_delay_ms(5);
}

void lcd_clear(void)
{
	lcd_cmd(0x01);
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
	uint8_t pos = (row == 0) ? 0x80 + col : 0xC0 + col;
	lcd_cmd(pos);
}

void lcd_print(char *str)
{
	while (*str)
	lcd_send(*str++, RS);
}