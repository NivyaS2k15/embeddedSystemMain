/*
 * i2c.c
 *
 * Created: 19-01-2026 14:15:12
 *  Author: NIVYA
 */ 
#define F_CPU      16000000UL   // 16 MHz clock

#include "i2c.h"
#include <avr/io.h>
#include <util/delay.h>

#define SCL_CLOCK  100000UL     // 100 kHz I2C speed

/* Initialize I2C (TWI) */
void I2C_Init(void) {
	TWSR = 0x00;   // Prescaler = 1
	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;  // Bit rate register
}

/* Send START condition */
void I2C_Start(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));  // Wait until start transmitted
}

/* Send STOP condition */
void I2C_Stop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	_delay_us(10);  // Small delay to ensure bus release
}

/* Write byte to I2C bus */
void I2C_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));  // Wait until data transmitted
}

/* Read byte with ACK (request more data) */
uint8_t I2C_Read_ACK(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));  // Wait until data received
	return TWDR;
}

/* Read byte with NACK (last byte) */
uint8_t I2C_Read_NACK(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));  // Wait until data received
	return TWDR;
}