/*
 * switch_high.c
 *
 * Created: 15-09-2025 16:00:37
 * Author : NIVYA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRD= 0b00001000; // set PD3 AS OUTPUT
	DDRC=0b00000000;  //SET PCO AS INPJUT
    /* Replace with your application code */
    while (1) 
    {
		if (PINC==0b00000001)
		{
			PORTD=0b00001000;
		}
		else
		{
			PORTD=0b00000000;
		}
    }
}

