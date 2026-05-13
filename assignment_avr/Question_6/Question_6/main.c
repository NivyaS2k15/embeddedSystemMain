/*
 * Question_6.c
 *
 * Created: 12-05-2026 10:38:37
 * Author : NIVYA
 */ 
/*
 * Traffic Light Controller with Deferred Emergency Interrupt
 * LEDs connected to PORTB:
 * PB0 -> Green LED
 * PB1 -> Orange LED
 * PB2 -> Red LED
 *
 * Emergency Button:
 * INT0 (PD2)
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t emergency_flag = 0;

/* -------- Interrupt Service Routine -------- */
ISR(INT0_vect)
{
    // Only set the flag
    emergency_flag = 1;
}

/* -------- Delay Function (1 second) -------- */
void delay_1s()
{
    for(int i = 0; i < 1000; i++)
    {
        _delay_ms(1);
    }
}

/* -------- Light Control Functions -------- */
void green_light()
{
    PORTB = (1 << PB0);
}

void orange_light()
{
    PORTB = (1 << PB1);
}

void red_light()
{
    PORTB = (1 << PB2);
}

/* -------- Main Program -------- */
int main(void)
{
    /* Configure LEDs as OUTPUT */
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);

    /* Configure INT0 pin (PD2) as INPUT */
    DDRD &= ~(1 << PD2);

    /* Enable pull-up resistor on PD2 */
    PORTD |= (1 << PD2);

    /* Configure INT0 for falling edge trigger */
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    /* Enable INT0 */
    EIMSK |= (1 << INT0);

    /* Enable Global Interrupts */
    sei();

    while (1)
    {
        /* -------- GREEN LIGHT -------- */
        green_light();

        for(int i = 0; i < 10; i++)
        {
            delay_1s();
        }

        /* Check emergency request after safe duration */
        if(emergency_flag)
        {
            green_light();

            for(int i = 0; i < 10; i++)
            {
                delay_1s();
            }

            emergency_flag = 0;
        }

        /* -------- ORANGE LIGHT -------- */
        orange_light();

        for(int i = 0; i < 3; i++)
        {
            delay_1s();
        }

        /* Check emergency request */
        if(emergency_flag)
        {
            green_light();

            for(int i = 0; i < 10; i++)
            {
                delay_1s();
            }

            emergency_flag = 0;
        }

        /* -------- RED LIGHT -------- */
        red_light();

        for(int i = 0; i < 10; i++)
        {
            delay_1s();
        }

        /* Check emergency request */
        if(emergency_flag)
        {
            green_light();

            for(int i = 0; i < 10; i++)
            {
                delay_1s();
            }

            emergency_flag = 0;
        }
    }
}