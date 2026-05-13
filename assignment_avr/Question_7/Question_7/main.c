#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

/*
PB1 -> Status LED (2 sec)
PB2 -> Heartbeat LED (500 ms)
*/

/* ---------------- TIMER1: 2 seconds ---------------- */
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PB1);
}

/* ---------------- TIMER2: 500 ms via 2 ms tick ---------------- */
ISR(TIMER2_COMPA_vect)
{
	static uint16_t count = 0;

	count++;  // every 2 ms

	if (count >= 250)   // 250 × 2 ms = 500 ms
	{
		PORTB ^= (1 << PB2);
		count = 0;
	}
}

int main(void)
{
	DDRB |= (1 << PB1) | (1 << PB2);

	PORTB = 0; // safe init

	/* ---------------- TIMER1 (CTC, 2 sec) ---------------- */
	TCCR1B |= (1 << WGM12);

	OCR1A = 31249;  // 2 sec @ 16MHz, prescaler 1024

	TIMSK1 |= (1 << OCIE1A);

	TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 1024

	/* ---------------- TIMER2 (CTC, 2 ms tick) ---------------- */
	TCCR2A |= (1 << WGM21);

	OCR2A = 249;  // 2 ms @ 16MHz, prescaler 128

	TIMSK2 |= (1 << OCIE2A);

	TCCR2B |= (1 << CS22) | (1 << CS20); // prescaler 128

	sei();

	while (1)
	{
		// fully interrupt-driven system
	}
}