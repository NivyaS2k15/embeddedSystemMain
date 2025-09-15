/*
 * DC_Motor_homework_FUnction.c
 *
 * Created: 15-09-2025 19:26:15
 * Author : NIVYA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void CW() {
	PORTB|= (1 << PORTB5);
	PORTB&= ~(1 << PORTB4);
}
void STOP() {
	PORTB &= ~(1 << PORTB5);
	PORTB &= ~(1 << PORTB4);
}
void ACW( ) {
	PORTB |= (1 << PORTB4);
	PORTB &= ~(1 << PORTB5);
}


int main(void)
{
	
	 DDRB |= (1 << DDB5);
	 DDRB |= (1 << DDB4); 


    /* Replace with your application code */
    while (1) 
    {
		CW();           // Clockwise
		_delay_ms(1000);

		STOP();         // Stop
		_delay_ms(5000);

		ACW();          // Anti-clockwise
		_delay_ms(1000);

    }
}

