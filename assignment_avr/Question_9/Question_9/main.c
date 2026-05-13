/*
 * Question_9.c
 *
 * Created: 12-05-2026 15:06:47
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON PD2   // push button input

uint8_t duty_index = 0;

// Duty cycle values: 25%, 50%, 75%, OFF
uint8_t duty_values[4] = {64, 128, 191, 0};

int main(void)
{
	/* ---------------- PWM OUTPUT PIN ---------------- */
	DDRD |= (1 << PD6);   // OC0A as output

	/* ---------------- BUTTON INPUT ---------------- */
	DDRD &= ~(1 << BUTTON);
	PORTD |= (1 << BUTTON);   // pull-up enabled

	/* ---------------- TIMER0 FAST PWM ---------------- */
	TCCR0A |= (1 << WGM01) | (1 << WGM00);  // Fast PWM
	TCCR0A |= (1 << COM0A1);                // non-inverting mode

	TCCR0B |= (1 << CS01) | (1 << CS00);    // prescaler 64

	OCR0A = duty_values[0];  // start at 25%

	while (1)
	{
		/* ---------------- BUTTON PRESS DETECT ---------------- */
		if (!(PIND & (1 << BUTTON)))
		{
			_delay_ms(30); // debounce delay

			if (!(PIND & (1 << BUTTON)))
			{
				duty_index++;

				if (duty_index > 3)
				duty_index = 0;

				OCR0A = duty_values[duty_index];

				/* wait for button release */
				while (!(PIND & (1 << BUTTON)));
				_delay_ms(30);
			}
		}
	}
}