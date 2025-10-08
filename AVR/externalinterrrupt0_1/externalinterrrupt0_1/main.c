#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

ISR(INT0_vect)
{
	PORTB^= (1 << PORTB5);
	_delay_ms(10000);
}

int main(void)
{
	DDRD &= ~(1 << DDD2);    // Making PD2 as input
	DDRB |= (1 << DDB5);  
	   // Making PB5 as output
     DDRB |= (1 << DDB4);  
	PORTD |= (1 << PORTD2);  // Enable internal pull-up on PD2

	EIMSK |= (1 << INT0);    // Enable INT0 interrupt
	EICRA |= (1 << ISC01);   // Trigger on falling edge
	sei();                   // Enable global interrupts

	while (1)
	{
		 PORTB^= (1 << PORTB4);
		 _delay_ms(2000);
	}
}