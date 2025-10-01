/*
 * timer0_overflow_INTERUPTS.c
 *
 * Created: 01-10-2025 12:43:44
 * Author : NIVYA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> //interrupt header 
  #include <stdint.h>
  
volatile  uint16_t count =0; 
  // interrupt service routine
  ISR(TIMER0_OVF_vect){       //TIMER_OVF_vect = this is interrupt vector table for  "address for the timer overflow  interrupt 
	  
	  if (count>=977)
	  {
		  PORTB ^=(1<<PORTB5);
		  count=0;
	  }
	  count++;
  }

int main(void)
{
	DDRB |=(1<<DDB5); //set output pord5
	//TCNT0=0;  becoz polling is not done here
	TCCR0A=0;  // normal mode
	TCCR0B |=(1<<CS00);
	TCCR0B |=(1<<CS01);  // 64 prescalar 
	
	
	// setting the interrupt so need of tifr flag register
TIMSK0 |=(1<<TOIE0); // NORMAL MODE /ENABLING TIMER OVERFLOW INTERRUPT
	sei(); // globally interrupt enable
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

