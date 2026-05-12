/*
 * Question_2.c
 *
 * Created: 11-05-2026 17:19:12
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define RED_LED   PD0   // Red LED connected to PORTD pin 0
#define GREEN_LED PD1   // Green LED connected to PORTD pin 1
#define BUTTON    PD2   // Push button connected to PORTD pin 2

int main(void) {
	// Configure LED pins as output
	DDRD |= (1 << RED_LED) | (1 << GREEN_LED);

	// Configure Button pin as input with pull-up
	DDRD &= ~(1 << BUTTON);     // Clear bit ? input
	PORTD |= (1 << BUTTON);     // Enable internal pull-up

	// Initial state: Red ON, Green OFF
	PORTD |= (1 << RED_LED);
	PORTD &= ~(1 << GREEN_LED);

	uint8_t ledState = 0; // 0 = Red ON, 1 = Green ON

	while (1) {
		// Check if button is pressed (active LOW)
		if (!(PIND & (1 << BUTTON))) {
			_delay_ms(50); // Debounce delay
			if (!(PIND & (1 << BUTTON))) { // Confirm press
				if (ledState == 0) {
					PORTD &= ~(1 << RED_LED);   // Turn OFF Red
					PORTD |= (1 << GREEN_LED);  // Turn ON Green
					ledState = 1;
					} else {
					PORTD &= ~(1 << GREEN_LED); // Turn OFF Green
					PORTD |= (1 << RED_LED);    // Turn ON Red
					ledState = 0;
				}
				// Wait until button is released
				while (!(PIND & (1 << BUTTON)));
			}
		}
	}
}
