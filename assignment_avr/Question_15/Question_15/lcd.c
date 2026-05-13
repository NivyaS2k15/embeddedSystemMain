#include "lcd.h"
#include <util/delay.h>

// ---------------- I2C (TWI) ----------------
void I2C_Init(void) {
	TWSR = 0x00;                // Prescaler = 1
	TWBR = 72;                  // SCL = 100kHz at 16MHz
}

static void I2C_Start(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

static void I2C_Stop(void) {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

static void I2C_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

// ---------------- LCD LOW-LEVEL ----------------
void LCD_WriteCmd(uint8_t cmd) {
	I2C_Start();
	I2C_Write(LCD_ADDR<<1);   // Write mode
	I2C_Write(0x00);          // Control byte: Co=0, RS=0
	I2C_Write(cmd);
	I2C_Stop();
}

void LCD_WriteData(uint8_t data) {
	I2C_Start();
	I2C_Write(LCD_ADDR<<1);   // Write mode
	I2C_Write(0x40);          // Control byte: Co=0, RS=1
	I2C_Write(data);
	I2C_Stop();
}

// ---------------- LCD INIT ----------------
void LCD_Init(void) {
	_delay_ms(50);            // Wait for LCD power up
	LCD_WriteCmd(0x38);       // Function set: 8-bit, 2 line
	LCD_WriteCmd(0x0C);       // Display ON, cursor OFF
	LCD_WriteCmd(0x01);       // Clear display
	_delay_ms(2);
	LCD_WriteCmd(0x06);       // Entry mode: increment
}

// ---------------- LCD STRING ----------------
void LCD_PrintString(const char *str) {
	while (*str) {
		LCD_WriteData(*str++);
	}
}

// ---------------- LCD CURSOR ----------------
void LCD_SetCursor(uint8_t row, uint8_t col) {
	uint8_t addr = (row == 0 ? 0x00 : 0x40) + col;
	LCD_WriteCmd(0x80 | addr);
}
