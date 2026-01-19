#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/* ---------- UART ---------- */
void UART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_Transmit(unsigned char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

/* ---------- SPI ---------- */
#define SS_PIN PB2

void SPI_MasterInit(void)
{
	DDRB |= (1 << PB3) | (1 << PB5) | (1 << SS_PIN); // MOSI, SCK, SS
	DDRB &= ~(1 << PB4);                            // MISO

	PORTB |= (1 << SS_PIN);                         // SS HIGH

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);  // SPI Master, fosc/16
}

void SPI_MasterTransmitBuffer(char *data, uint8_t len)
{
	PORTB &= ~(1 << SS_PIN);     // SS LOW (start frame)

	for(uint8_t i = 0; i < len; i++)
	{
		SPDR = data[i];
		while(!(SPSR & (1 << SPIF)));
	}

	PORTB |= (1 << SS_PIN);      // SS HIGH (end frame)
}

/* ---------- MAIN ---------- */
int main(void)
{
	SPI_MasterInit();
	UART_Init(103); // 9600 baud

	char msg[3] = {'h','a','i'};

	while(1)
	{
		SPI_MasterTransmitBuffer(msg, 3);

		UART_Transmit('h');
		UART_Transmit('a');
		UART_Transmit('i');
		UART_Transmit('\n');

		_delay_ms(1000);
	}
}
