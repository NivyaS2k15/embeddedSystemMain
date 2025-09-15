#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
void delay_ms_variable(int p) {
	while (p--) {
		_delay_ms(1); // Each iteration delays 1 ms
	}
}


void CW(int p) {
	PORTB |= (1 << PORTB5);
	PORTB &= ~(1 << PORTB4);
delay_ms_variable(p);

}

void STOP(int p) {
	PORTB &= ~(1 << PORTB5);
	PORTB &= ~(1 << PORTB4);
	delay_ms_variable(p);

}

void ACW(int p) {
	PORTB |= (1 << PORTB4);
	PORTB &= ~(1 << PORTB5);
	delay_ms_variable(p);

}

int main(void)
{
	DDRB |= (1 << DDB5); // Set PB5 as output
	DDRB |= (1 << DDB4); // Set PB4 as output

	while (1)
	{
		CW(1000);     // Clockwise for 1 sec
		STOP(5000);   // Stop for 5 sec
		ACW(1000);    // Anti-clockwise for 1 sec
		
	}
}