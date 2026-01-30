/*
 * servo.c
 *
 * Created: 19-01-2026 12:40:12
 *  Author: NIVYA
 */ 
#include "servo.h"

void Servo_init(void) {
	DDRB |= (1 << PB1); // OC1A pin as output

	// Fast PWM, mode 14: ICR1 as TOP
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
	ICR1 = 39999; // 20 ms period (50 Hz) at 16 MHz / 8
}

void Servo_write(uint8_t angle) {
	// Map 0–180° to 1000–2000 µs pulse
	uint16_t pulse = 1000 + ((angle * 1000) / 180);
	OCR1A = pulse * 2; // Each tick = 0.5 µs
}