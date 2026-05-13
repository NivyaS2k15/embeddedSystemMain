#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char count = 0;

// Function to display binary value on LEDs
void displayBinary(unsigned char value)
{
	PORTB = (value & 0x0F);   // Display only lower 4 bits
}

// Timer0 delay function (approx 50 ms)
void timer0_delay()
{
	TCNT0 = 0;

	// Prescaler = 1024
	TCCR0 = (1 << CS02) | (1 << CS00);

	while (!(TIFR & (1 << TOV0)));

	TIFR |= (1 << TOV0);

	TCCR0 = 0;
}

int main(void)
{
	// PB0–PB3 as outputs
	DDRB = 0x0F;

	// PD2 as input
	DDRD &= ~(1 << PD2);

	// Enable internal pull-up resistor
	PORTD |= (1 << PD2);

	displayBinary(count);

	while (1)
	{
		// Button pressed
		if (!(PIND & (1 << PD2)))
		{
			timer0_delay(); // Debounce using Timer0

			if (!(PIND & (1 << PD2)))
			{
				count++;

				// Reset after 15
				if (count > 15)
				{
					count = 0;
				}

				displayBinary(count);

				// Wait for button release
				while (!(PIND & (1 << PD2)));
			}
		}
	}
}