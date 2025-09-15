/*
 * DC_MOTOR.c
 *
 * Created: 15-09-2025 19:16:27
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB5);
	DDRB |= (1 << DDB4);   // Set PB5 as output

	while (1)
	{
		PORTB |= (1 << PORTB5);   // Turn LED ON
	
		PORTB &= ~(1 << PORTB4);  // Turn LED OFF
		_delay_ms(1000);
	    PORTB &= ~(1 << PORTB5);
	    PORTB &= ~(1 << PORTB4);
		_delay_ms(5000);
		
		PORTB |= (1 << PORTB4);   // Turn LED ON
		
		PORTB &= ~(1 << PORTB5);
		_delay_ms(1000);
		
		
	}
}
