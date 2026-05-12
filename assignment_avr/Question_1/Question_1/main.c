#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void delay_ms_custom(unsigned int ms)
{
	while(ms--)
	{
		_delay_ms(1);
	}
}

int main(void)
{
	// Set PD5 as output
	DDRD |= (1 << PD5);

	while(1)
	{
		// LED ON
		PORTD |= (1 << PD5);

		// 3 second delay
		delay_ms_custom(3000);

		// LED OFF
		PORTD &= ~(1 << PD5);

		// 5 second delay
		delay_ms_custom(5000);
	}
}