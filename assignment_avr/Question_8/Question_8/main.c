/*
 * Question_8.c
 *
 * Created: 12-05-2026 14:12:20
 * Author : NIVYA
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BUTTON   PD2   // Push button input pin
#define LED_PIN  PD6   // OC0A output pin

volatile uint8_t dutyLevel = 0; // 0=25%, 1=50%, 2=75%, 3=OFF

// Function to update PWM duty cycle
void updatePWM(uint8_t level) {
	switch(level) {
		case 0: OCR0A = 64;  break;   // 25% duty (64/255)
		case 1: OCR0A = 128; break;   // 50% duty
		case 2: OCR0A = 192; break;   // 75% duty
		case 3: OCR0A = 0;   break;   // OFF
	}
}

ISR(INT0_vect) {
	// On button press, cycle duty level
	dutyLevel = (dutyLevel + 1) & 0x03; // Wrap 0–3
	updatePWM(dutyLevel);
}

int main(void) {
	// Configure LED pin (PD6/OC0A) as output
	DDRD |= (1 << LED_PIN);

	// Configure button pin (PD2/INT0) as input with pull-up
	DDRD &= ~(1 << BUTTON);
	PORTD |= (1 << BUTTON);

	// --- Timer0 Fast PWM Setup ---
	TCCR0A |= (1 << WGM00) | (1 << WGM01);   // Fast PWM mode
	TCCR0A |= (1 << COM0A1);                 // Non-inverting output on OC0A
	TCCR0B |= (1 << CS01) | (1 << CS00);     // Prescaler = 64

	OCR0A = 64; // Start with 25% duty cycle

	// --- External Interrupt INT0 Setup ---
	EICRA |= (1 << ISC01); // Trigger on falling edge
	EIMSK |= (1 << INT0);  // Enable INT0

	sei(); // Enable global interrupts

	while (1) {
		// Main loop does nothing; PWM + ISR handle everything
	}
}





