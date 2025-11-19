#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)  // UBRR = 103
#include "uart.h"

int main(void)
{
	uint32_t adc_temp;

	DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2); // MOSI, SCK, SS as outputs
	DDRB &= ~(1 << PB4);                           // MISO as input
	PORTB |= (1 << PB2);                           // SS high initially
	DDRD|=(1<<PD3);
	// ===== SPI SETUP =====
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI Master

	_delay_ms(100); // allow BMP280 to power up

	// ===== READ CHIP ID =====
	PORTB &= ~(1 << PB2); // CSB low
	SPDR = (0xFA)|(0x80);
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	SPDR = 0x00;
	while (!(SPSR & (1 << SPIF)));
	adc_temp = ((uint32_t)SPDR << 12);
	
	
	

	
	
	// READING FB 
	PORTB &= ~(1 << PB2); // CSB low
	SPDR = (0xFB)|(0x80);
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	SPDR = 0x00;
	while (!(SPSR & (1 << SPIF)));
	adc_temp = ((uint32_t)SPDR << 4);
	
	// READING FC
	
		PORTB &= ~(1 << PB2); // CSB low
		SPDR = (0xFC)|(0x80);
		while (!(SPSR & (1 << SPIF)));
		(void)SPDR;
		SPDR = 0x00;
		while (!(SPSR & (1 << SPIF)));
		adc_temp = ((uint32_t)SPDR >>4);
	UART_TxHex(adc_temp);
	
		

	

	while (1)
	{
		
		
	}
}