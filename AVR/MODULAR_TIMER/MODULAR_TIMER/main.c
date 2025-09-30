/*
 * MODULAR_TIMER.c
 *
 * Created: 30-09-2025 18:42:34
 * Author : NIVYA
 */ 

#define  F_CPU 16000000UL
#include "NIVYA.h"
#include <avr/io.h>
#include <stdint.h>
#include "gpio.h"


int main(void)
{
	pin_initialization();
	timer_init();
    /* Replace with your application code */
    while (1) 
    {
		PORTD |= (1 << PORTD0);  // LED0 ON
		PORTD |= (1 << PORTD1);  // LED1 ON
		PORTD |= (1 << PORTD2);  // LED2 ON
		PORTD |= (1 << PORTD3);  // LED3 ON
		PORTD |= (1 << PORTD4);  // LED4 ON
		kichu(2000);              // 2-second delay

		PORTD &= ~(1 << PORTD0);  // LED0 OFF
		PORTD &= ~(1 << PORTD1);  // LED1 OFF
		PORTD &= ~(1 << PORTD2);  // LED2 OFF
		PORTD &= ~(1 << PORTD3);  // LED3 OFF
		PORTD &= ~(1 << PORTD4);  // LED4 OFF
		kichu(2000);               // 2-second delay
		
		
    }
}

