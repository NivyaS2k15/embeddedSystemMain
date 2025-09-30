/*
 * timer0_CTM.c
 *
 * Created: 29-09-2025 15:27:23
 * Author : NIVYA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
	
	DDRB |=(1<<DDB5); // OUTPUT IS SET PIN B 5
	TCCR0A |=(1<<WGM01); //CTC MODE SET 
	OCR0A = 200; // THIS IS SET FOR COMPARING AND LESS THAN 255 FOR 8IT COUNTER
	TCNT0 =0;
	TCCR0B |=(1<<CS00); // No prescaling 
	TIFR0  |=(1<<OCF0A) ; //SET FLAG TO INITAL STATE

    /* Replace with your application code */
    while (1) 
    {
		PORTB ^=(1<<PORTB5);
		
		for (long int i=0;i<160000;i++){
			while(!(TIFR0&(1<<OCF0A))){
				
			}
			TIFR0  |=(1<<OCF0A);
		}
			
		
	}
}

