#define F_CPU 16000000UL
#include <avr/io.h>

void delay_5s(void)
{
	for (int i = 0; i < 6250; i++)   // 5sec second
	{
		while (!(TIFR0 & (1 << OCF0A)));  // Wait until compare match
		TIFR0 |= (1 << OCF0A);            // Clear flag
	}
}

int main(void)
{
	DDRB |= (1 << DDB5);
	DDRB |= (1 << DDB4);                 // Set PB5 as output

	TCCR0A |= (1 << WGM01);              // CTC mode
	OCR0A = 200;                         // Compare value
	TCNT0 = 0;
	TCCR0B |= (1 << CS00) | (1 << CS01); // Prescaler = 64

	TIFR0 |= (1 << OCF0A);               // Clear flag before loop

	while (1)
	{
		PORTB |= (1 << PORTB5);          // LED ON
		delay_5s();
		PORTB &= ~(1 << PORTB5);         // LED OFF
		delay_5s();
		PORTB |= (1 << PORTB4);          // LED ON
		delay_5s();
		PORTB &= ~(1 << PORTB4);         // LED OFF
		delay_5s();
	}
}
