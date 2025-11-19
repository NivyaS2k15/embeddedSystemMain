#define F_CPU 16000000UL
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t lsb, msb;
	uint16_t dig_T1;
	uint16_t dig_T2;
	int dig_T3;
	
	
	
	float var1, var2, temperature;
	int32_t t_fine;
	int32_t adc_temp=52000;
	

	UART_Init();

	DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2); // MOSI, SCK, SS outputs
	DDRB &= ~(1 << PB4);                           // MISO input
	PORTB |= (1 << PB2);                           // SS high initially

	DDRD |= (1 << PD3);

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI Master, fosc/16

	_delay_ms(100); // allow BMP280 to power up

	PORTB &= ~(1 << PB2);           // SS low to start transaction
	_delay_us(1);

	SPDR = 0x88 | 0x80;             // send register address with read bit
	while (!(SPSR & (1 << SPIF)));  // wait for transfer complete
	(void)SPDR;                     // discard received byte (dummy)

	SPDR = 0x00;                    // clock out LSB
	while (!(SPSR & (1 << SPIF)));
	lsb = SPDR;                     // read LSB (0x88)

	SPDR = 0x00;                    // clock out MSB
	while (!(SPSR & (1 << SPIF)));
	msb = SPDR;                     // read MSB (0x89)

	_delay_us(1);
	PORTB |= (1 << PB2);            // SS high to end transaction

	dig_T1 = (uint16_t)msb << 8 | lsb;
	
	
	
	
	
	
	
	
	// dig _2
	
	PORTB &= ~(1 << PB2); 
	SPDR = 0x8A | 0x80;             // send register address with read bit
	while (!(SPSR & (1 << SPIF)));  // wait for transfer complete
	(void)SPDR;                     // discard received byte (dummy)

	SPDR = 0x00;                    // clock out LSB
	while (!(SPSR & (1 << SPIF)));
	lsb = SPDR;                     // read LSB (0x88)

	SPDR = 0x00;                    // clock out MSB
	while (!(SPSR & (1 << SPIF)));
	msb = SPDR;
	_delay_us(1);
	PORTB |= (1 << PB2);
	 
	dig_T2 = (uint16_t)msb << 8 | lsb;
	
	
	//dig_3
	PORTB &= ~(1 << PB2);
	SPDR = 0x8C| 0x80;             // send register address with read bit
	while (!(SPSR & (1 << SPIF)));  // wait for transfer complete
	(void)SPDR;                     // discard received byte (dummy)

	SPDR = 0x00;                    // clock out LSB
	while (!(SPSR & (1 << SPIF)));
	lsb = SPDR;                     // read LSB (0x88)

	SPDR = 0x00;                    // clock out MSB
	while (!(SPSR & (1 << SPIF)));
	msb = SPDR;
	_delay_us(1);
	PORTB |= (1 << PB2);
	
	dig_T3 = (uint16_t)msb << 8 | lsb;
    
 




var1 = (((float)adc_temp / 16384.0) - ((float)dig_T1 / 1024.0)) * (float)dig_T2;
var2 = ((((float)adc_temp / 131072.0) - ((float)dig_T1 / 8192.0)) *
(((float)adc_temp / 131072.0) - ((float)dig_T1 / 8192.0))) * (float)dig_T3;

t_fine = (int32_t)(var1 + var2);
temperature = t_fine / 5120.0;   // in °C

	while (1) {

	UART_TxString("t_fine");
	 UART_TxChar('\n');
	UART_TxNumber(t_fine);
	_delay_ms(1000)  ;
	UART_TxChar('\n');
	_delay_ms(1000)  ;
	UART_TxString("temperature");
	UART_TxChar('\n');
	UART_TxNumber(temperature);
	_delay_ms(1000)  ;
	
	 }
}