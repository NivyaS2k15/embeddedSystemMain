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
  ISR(TIMER0_COMPA_vect){       //TIMER_OVF_vect = this is interrupt vector table for  "address for the timer overflow  interrupt 
	  
	  if (count>=1245)
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
	TCCR0A |=(1<<WGM01);  // ctc mode
	OCR0A = 200; 
	TCCR0B |=(1<<CS00);
	TCCR0B |=(1<<CS01);  // 64 prescalar 
	
	
	

    TIMSK0 |= (1 << OCIE0A);  // ctc mode /ENABLING TIMER OVERFLOW INTERRUPT
	sei(); // globally interrupt enable
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

