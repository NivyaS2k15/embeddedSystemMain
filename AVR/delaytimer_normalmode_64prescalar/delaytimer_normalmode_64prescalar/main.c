/*
 * delaytimer0_normal.c
 *
 * Created: 29-09-2025 11:12:43
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

    void delay_1s(void){
		unsigned int i;
		unsigned int count =976;
	for ( i=0;i<count;i++)
	{
		TCNT0 =0;
		TCCR0A=0;
		TCCR0B |=(1<<CS00);
		TCCR0B |=(1<<CS01); // prescalar 1|64;
		TIFR0 |=(1<< TOV0); //SET T0 ZERO
		while(!(TIFR0 & (1<<TOV0)));  // 16MICRO SECONDS  // LOOP WORK UNTIL THIS CONDITION SATISFIES ZERO
	}
		
	}
int main(void)
{
	
	DDRB |= (1 << DDB5); // set as an output 
    /* Replace with your application code */
    while (1) 
    {
		PORTB |=(1<<PORTB5);
		delay_1s();
		PORTB &= ~(1 << PORTB5); 
		delay_1s();
    }
}

