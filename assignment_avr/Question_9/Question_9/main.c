#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON PD2

uint8_t duty_index = 0;

// 25%, 50%, 75%, 100%
uint8_t duty_values[4] = {64, 128, 191, 255};

int main(void)
{
	// -----------------------------------
	// PWM OUTPUT (OC0A -> PD6)
	// -----------------------------------
	DDRD |= (1 << PD6);

	// -----------------------------------
	// BUTTON INPUT
	// -----------------------------------
	DDRD &= ~(1 << BUTTON);

	// Enable pull-up
	PORTD |= (1 << BUTTON);

	// -----------------------------------
	// TIMER0 FAST PWM MODE
	// -----------------------------------
	TCCR0A |= (1 << WGM01) | (1 << WGM00);

	// Non-inverting PWM
	TCCR0A |= (1 << COM0A1);

	// Prescaler = 64
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Initial 25%
	OCR0A = duty_values[duty_index];

	while (1)
	{
		// Button pressed
		if (!(PIND & (1 << BUTTON)))
		{
			_delay_ms(30);

			if (!(PIND & (1 << BUTTON)))
			{
				duty_index++;

				if (duty_index >= 4)
				{
					duty_index = 0;
				}

				OCR0A = duty_values[duty_index];

				// Wait for release
				while (!(PIND & (1 << BUTTON)));

				_delay_ms(30);
			}
		}
	}
}