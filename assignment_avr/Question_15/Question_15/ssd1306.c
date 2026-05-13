/*
 * ssd1306.c
 *
 * Created: 13-05-2026 15:27:53
 *  Author: NIVYA
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "ssd1306.h"

// ---------------- SEND COMMAND ----------------
void ssd1306_command(uint8_t cmd)
{
	i2c_start();
	i2c_write(OLED_ADDR << 1);
	i2c_write(0x00);   // command mode
	i2c_write(cmd);
	i2c_stop();
}

// ---------------- INIT OLED ----------------
void ssd1306_init(void)
{
	_delay_ms(100);

	ssd1306_command(0xAE);
	ssd1306_command(0x20);
	ssd1306_command(0x10);
	ssd1306_command(0xB0);
	ssd1306_command(0xC8);
	ssd1306_command(0x00);
	ssd1306_command(0x10);
	ssd1306_command(0x40);
	ssd1306_command(0x81);
	ssd1306_command(0xFF);
	ssd1306_command(0xA1);
	ssd1306_command(0xA6);
	ssd1306_command(0xA8);
	ssd1306_command(0x3F);
	ssd1306_command(0xA4);
	ssd1306_command(0xD3);
	ssd1306_command(0x00);
	ssd1306_command(0xD5);
	ssd1306_command(0xF0);
	ssd1306_command(0xD9);
	ssd1306_command(0x22);
	ssd1306_command(0xDA);
	ssd1306_command(0x12);
	ssd1306_command(0xDB);
	ssd1306_command(0x20);
	ssd1306_command(0x8D);
	ssd1306_command(0x14);
	ssd1306_command(0xAF);
}

// ---------------- CLEAR (simple fill 0) ----------------
void ssd1306_clear(void)
{
	for (uint16_t i = 0; i < 1024; i++)
	{
		i2c_start();
		i2c_write(OLED_ADDR << 1);
		i2c_write(0x40);
		i2c_write(0x00);
		i2c_stop();
	}
}

// ---------------- SET CURSOR (simplified) ----------------
void ssd1306_set_cursor(uint8_t row, uint8_t col)
{
	ssd1306_command(0xB0 + row);
	ssd1306_command(0x00 + (col & 0x0F));
	ssd1306_command(0x10 + (col >> 4));
}

// ---------------- PRINT STRING (VERY SIMPLE ASCII MAP NEEDED) ----------------
void ssd1306_print(char *str)
{
	while (*str)
	{
		i2c_start();
		i2c_write(OLED_ADDR << 1);
		i2c_write(0x40);
		i2c_write(*str++);
		i2c_stop();
	}
}