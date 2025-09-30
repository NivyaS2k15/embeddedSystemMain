/*
 * NIVYA.c
 *
 * Created: 30-09-2025 19:32:23
 *  Author: NIVYA
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


void timer_init(void){
	TCCR0A|=(1<<WGM01) ;//CTC MODE SET
	OCR0A=249;
	TCNT0=0;
	TCCR0B|=(1<<CS00); // SET 64
	TCCR0B|=(1<<CS01);
	TIFR0|=(1<<OCF0A); //  FLAG SET TO ZERO
	
	
}
void kichu(uint16_t ms){
	while (ms--) {
		while (!(TIFR0 & (1 << OCF0A))) {
			// wait for compare match
		}
		TIFR0 |= (1 << OCF0A); // clear flag
	}
}