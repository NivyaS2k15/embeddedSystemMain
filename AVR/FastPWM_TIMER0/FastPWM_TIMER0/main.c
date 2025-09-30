#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1 << DDD6);           // Set PD6 (OC0A) as output

	TCCR0A |= (1 << WGM01) | (1 << WGM00);  // Fast PWM mode
	TCCR0A |= (1 << COM0A1);       // Non-inverting mode on OC0A
	TCCR0B |= (1 << CS00) | (1 << CS01);    // Prescaler = 64

	OCR0A = 200;                   // Duty cycle = 100/256 ? 39.1%

	while (1)
	{
		// PWM runs automatically—no need to toggle manually
	}
}