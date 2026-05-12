/*
 * Question_4.c
 *
 * Created: 11-05-2026 18:30:20
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char count = 0;

// Function to display binary count on LEDs
void displayBinary(unsigned char value)
{
	PORTB = (value & 0x0F); // Use only PB0–PB3
}

int main(void)
{
	// PB0–PB3 as output for LEDs
	DDRB = 0x0F;

	// PD2 as input for switch
	DDRD &= ~(1 << PD2);

	// Enable pull-up resistor on PD2
	PORTD |= (1 << PD2);

	displayBinary(count);

	while (1)
	{
		// Switch pressed (active LOW)
		if (!(PIND & (1 << PD2)))
		{
			_delay_ms(50); // Debounce delay

			if (!(PIND & (1 << PD2)))
			{
				count++;

				// Reset after 15
				if (count > 15)
				{
					count = 0;
				}

				displayBinary(count);

				// Wait until switch released
				while (!(PIND & (1 << PD2)));
			}
		}
	}
}

