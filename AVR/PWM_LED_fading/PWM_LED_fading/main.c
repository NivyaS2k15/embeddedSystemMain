#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1 << DDD6);  // PD6 (OC0A) as output

	// Fast PWM mode, non-inverting on OC0A
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0A |= (1 << COM0A1);
	TCCR0B |= (1 << CS01) | (1 << CS00);   // Prescaler = 64

	while (1)
	{
		
		for (int i = 0; i < 256; i++)
		{
			OCR0A = i;       // Duty cycle changes from 0 ? 255
			_delay_ms(20);   
		}

		
		for (int i = 255; i >= 0; i--)
		{
			OCR0A = i;       // Duty cycle changes from 255 ? 0
			_delay_ms(20);
		}
	}
}
