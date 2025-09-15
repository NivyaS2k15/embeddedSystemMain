/*
 * switch_low.c
 *
 * Created: 15-09-2025 16:08:33
 * Author : NIVYA
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	DDRD=0b00001000; //output
	DDRC=0b00000000; //input
	PORTC=0b00000001; //pull up internal
    /* Replace with your application code */
    while (1) 
    {
		if (PINC==0b00000000)  //active low
		{
			PORTD=0b00001000;
		} 
		else
		{
			PORTD=0b00000000;
		}
    }
}

