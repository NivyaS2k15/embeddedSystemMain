/*
 * ssd1306.h
 *
 * Created: 19-01-2026 14:11:18
 *  Author: NIVYA
 */ 


#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>

/* I2C address for SSD1306 (most modules use 0x3C) */
#define SSD1306_ADDRESS 0x3C

/* OLED dimensions */
#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT   64

/* Function prototypes */
void SSD1306_Init(void);
void SSD1306_SendCommand(uint8_t cmd);
void SSD1306_SendData(uint8_t data);
void SSD1306_Clear(void);
void SSD1306_UpdateScreen(void);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void SSD1306_DrawChar7x10(uint8_t x, uint8_t y, char c);
void SSD1306_DrawString7x10(uint8_t x, uint8_t y, const char* str);

#endif /* SSD1306_H_ */