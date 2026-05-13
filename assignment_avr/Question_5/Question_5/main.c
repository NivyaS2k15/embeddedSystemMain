#include <avr/io.h>
#include <avr/interrupt.h>

#define GREEN_LED PB0
#define ORANGE_LED PB1
#define RED_LED PB2

volatile unsigned long timer_ms = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;   // preload for ~1ms
	timer_ms++;
}

int main(void)
{
	DDRB |= (1 << GREEN_LED) | (1 << ORANGE_LED) | (1 << RED_LED);

	// Timer0 init
	TCCR0B |= (1 << CS01) | (1 << CS00); // prescaler 64
	TIMSK0 |= (1 << TOIE0);
	TCNT0 = 6;

	sei();

	unsigned long start;

	while (1)
	{
		PORTB = (1 << GREEN_LED);
		start = timer_ms;
		while ((timer_ms - start) < 10000);

		PORTB = (1 << ORANGE_LED);
		start = timer_ms;
		while ((timer_ms - start) < 3000);

		PORTB = (1 << RED_LED);
		start = timer_ms;
		while ((timer_ms - start) < 10000);
	}
}