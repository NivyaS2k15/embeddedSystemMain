/*
 * DC_MOTOR.c
 *
 * Created: 15-09-2025 19:16:27
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDB5);
	DDRB |= (1 << DDB4);   // Set PB5 as output
	DDRD &= ~(1<<DDD2);  //set d2 as input
	

	while (1)
	{
		if(PIND &(1<<PIND2)) 
		{             // pull down resistor  
			
		
		PORTB |= (1 << PORTB5);   // Turn LED ON
	    PORTB &= ~(1 << PORTB4);  // Turn LED OFF
		_delay_ms(2000);  //cw
	    PORTB &= ~(1 << PORTB5);
	    PORTB &= ~(1 << PORTB4);
		_delay_ms(5000);  //stop
		
		PORTB |= (1 << PORTB4);   // Turn LED ON
		PORTB &= ~(1 << PORTB5);
		_delay_ms(2000);  //acw
		 PORTB &= ~(1 << PORTB5);
		 PORTB &= ~(1 << PORTB4);
		 _delay_ms(5000); //stop
		}else{
               PORTB &= ~(1 << PORTB5);
               PORTB &= ~(1 << PORTB4);
           		}
		
		
		}
}
