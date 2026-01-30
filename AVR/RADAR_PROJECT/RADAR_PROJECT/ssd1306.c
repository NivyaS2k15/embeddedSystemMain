#include "ssd1306.h"
#include "i2c.h"
#include "fonts.h"
#include <avr/io.h>
#include <util/delay.h>
extern const uint16_t Font7x10[];
/* Framebuffer */
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

/* Send a command byte */
void SSD1306_SendCommand(uint8_t cmd) {
	I2C_Start();
	I2C_Write((SSD1306_ADDRESS << 1) | 0); // Write mode
	I2C_Write(0x00); // Control byte: command
	I2C_Write(cmd);
	I2C_Stop();
}

/* Send a data byte */
void SSD1306_SendData(uint8_t data) {
	I2C_Start();
	I2C_Write((SSD1306_ADDRESS << 1) | 0); // Write mode
	I2C_Write(0x40); // Control byte: data
	I2C_Write(data);
	I2C_Stop();
}

/* Initialize OLED */
void SSD1306_Init(void) {
	_delay_ms(100);

	SSD1306_SendCommand(0xAE); // Display off
	SSD1306_SendCommand(0x20); // Memory addressing mode
	SSD1306_SendCommand(0x00); // Horizontal addressing
	SSD1306_SendCommand(0xB0);
	SSD1306_SendCommand(0xC8);
	SSD1306_SendCommand(0x00);
	SSD1306_SendCommand(0x10);
	SSD1306_SendCommand(0x40);
	SSD1306_SendCommand(0x81);
	SSD1306_SendCommand(0xFF);
	SSD1306_SendCommand(0xA1);
	SSD1306_SendCommand(0xA6);
	SSD1306_SendCommand(0xA8);
	SSD1306_SendCommand(0x3F);
	SSD1306_SendCommand(0xA4);
	SSD1306_SendCommand(0xD3);
	SSD1306_SendCommand(0x00);
	SSD1306_SendCommand(0xD5);
	SSD1306_SendCommand(0xF0);
	SSD1306_SendCommand(0xD9);
	SSD1306_SendCommand(0x22);
	SSD1306_SendCommand(0xDA);
	SSD1306_SendCommand(0x12);
	SSD1306_SendCommand(0xDB);
	SSD1306_SendCommand(0x20);
	SSD1306_SendCommand(0x8D);
	SSD1306_SendCommand(0x14);
	SSD1306_SendCommand(0xAF); // Display on

	SSD1306_Clear();
	SSD1306_UpdateScreen();
}

/* Clear buffer */
void SSD1306_Clear(void) {
	for (uint16_t i = 0; i < sizeof(SSD1306_Buffer); i++) {
		SSD1306_Buffer[i] = 0x00;
	}
}

/* Push buffer to OLED */
void SSD1306_UpdateScreen(void) {
	for (uint8_t page = 0; page < 8; page++) {
		SSD1306_SendCommand(0xB0 + page);
		SSD1306_SendCommand(0x00);
		SSD1306_SendCommand(0x10);
		for (uint8_t col = 0; col < SSD1306_WIDTH; col++) {
			SSD1306_SendData(SSD1306_Buffer[page * SSD1306_WIDTH + col]);
		}
	}
}

/* Draw pixel in buffer */
void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color) {
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;

	if (color)
	SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= (1 << (y % 8));
	else
	SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
}

/* Draw one character (7x10 font) */
void SSD1306_DrawChar7x10(uint8_t x, uint8_t y, char c) {
	uint16_t bitmap;
	for (uint8_t row = 0; row < 10; row++) {
		bitmap = Font7x10[(c - 32) * 10 + row];
		for (uint8_t col = 0; col < 7; col++) {
			if (bitmap & (1 << (6 - col)))
			SSD1306_DrawPixel(x + col, y + row, 1);
			else
			SSD1306_DrawPixel(x + col, y + row, 0);
		}
	}
}

/* Draw string */
void SSD1306_DrawString7x10(uint8_t x, uint8_t y, const char* str) {
	while (*str) {
		SSD1306_DrawChar7x10(x, y, *str++);
		x += 8; // 7 pixels + 1 spacing
		if (x + 7 >= SSD1306_WIDTH) {
			x = 0;
			y += 11; // move to next line
		}
	}
}