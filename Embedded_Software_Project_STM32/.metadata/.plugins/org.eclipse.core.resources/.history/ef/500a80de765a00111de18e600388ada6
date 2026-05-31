/*
 * i2c_lcd.h
 * Custom I2C LCD Driver for HD44780 + PCF8574 Backpack
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H

#include "stm32f446xx_i2c_driver.h"

// Set your LCD I2C Slave Address (Typically 0x27 or 0x3F for PCF8574)
#define LCD_SLAVE_ADDR         0x27

// HD44780 LCD Command Set
#define LCD_CMD_CLEAR_DISPLAY   0x01
#define LCD_CMD_RETURN_HOME     0x02
#define LCD_CMD_ENTRY_MODE_SET  0x04
#define LCD_CMD_DISPLAY_CONTROL 0x08
#define LCD_CMD_CURSOR_SHIFT    0x10
#define LCD_CMD_FUNCTION_SET    0x20
#define LCD_CMD_SET_CGRAM_ADDR  0x40
#define LCD_CMD_SET_DDRAM_ADDR  0x80

// Display Control Flags
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_BLINK_OFF           0x00
#define LCD_CMD_SET_DDRAM_ADDR  0x80
#define LCD_CMD_DDRAM_ADDR      0x80  // Add this line
// PCF8574 Pin Mapping Bitmasks to LCD Layout
#define LCD_PIN_RS              (1 << 0)  // Register Select (0: Command, 1: Data)
#define LCD_PIN_RW              (1 << 1)  // Read/Write (0: Write, 1: Read)
#define LCD_PIN_EN              (1 << 2)  // Enable Pulse Line
#define LCD_PIN_BACKLIGHT       (1 << 3)  // Backlight Control Bit

// Function Prototypes
void LCD_Init(I2C_Handle_t *pI2CHandle);
void LCD_SendCommand(I2C_Handle_t *pI2CHandle, uint8_t cmd);
void LCD_SendData(I2C_Handle_t *pI2CHandle, uint8_t data);
void LCD_SendString(I2C_Handle_t *pI2CHandle, char *str);
void LCD_SetCursor(I2C_Handle_t *pI2CHandle, uint8_t row, uint8_t col);
void LCD_Clear(I2C_Handle_t *pI2CHandle);

#endif /* I2C_LCD_H */
