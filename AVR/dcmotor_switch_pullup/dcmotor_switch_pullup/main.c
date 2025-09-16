#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB5);  // PB5 as output
	DDRB |= (1 << DDB4);  // PB4 as output
	DDRD &= ~(1 << DDD2); // PD2 as input
	PORTD |= (1 << PORTD2); // Enable internal pull-up on PD2

	while (1)
	{
		if (!(PIND & (1 << PIND2))) // Check if button is pressed (LOW)
		{
			// Rotate motor clockwise
			PORTB |= (1 << PORTB5);
			PORTB &= ~(1 << PORTB4);
			_delay_ms(2000);

			// Stop motor
			PORTB &= ~(1 << PORTB5);
			PORTB &= ~(1 << PORTB4);
			_delay_ms(5000);

			// Rotate motor anti-clockwise
			PORTB |= (1 << PORTB4);
			PORTB &= ~(1 << PORTB5);
			_delay_ms(2000);

			// Stop motor
			PORTB &= ~(1 << PORTB5);
			PORTB &= ~(1 << PORTB4);
			_delay_ms(5000);
		}
		else
		{
			// Stop motor if button not pressed
			PORTB &= ~(1 << PORTB5);
			PORTB &= ~(1 << PORTB4);
		}
	}
}
