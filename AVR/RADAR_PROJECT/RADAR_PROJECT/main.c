/*
 * RADAR_PROJECT.c
 *
 * Created: 19-01-2026
 * Author : Nivya
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "servo.h"

#define TRIG_PIN PD2
#define ECHO_PIN PD3
#define BUZZER_PIN PB0

// ---- Ultrasonic functions ----
void Ultrasonic_init(void) {
    DDRD |= (1 << TRIG_PIN);   // TRIG output
    DDRD &= ~(1 << ECHO_PIN);  // ECHO input
}

uint16_t Ultrasonic_read(void) {
    // Trigger pulse
    PORTD &= ~(1 << TRIG_PIN);
    _delay_us(2);
    PORTD |= (1 << TRIG_PIN);
    _delay_us(10);
    PORTD &= ~(1 << TRIG_PIN);

    // Wait for echo start (with timeout)
    uint16_t timeout = 60000;
    while (!(PIND & (1 << ECHO_PIN)) && timeout--) ;
    if (timeout == 0) return 0;

    TCNT1 = 0;

    // Wait for echo end (with timeout)
    timeout = 60000;
    while ((PIND & (1 << ECHO_PIN)) && timeout--) ;
    if (timeout == 0) return 0;

    uint16_t duration = TCNT1;

    // Convert to distance in cm (integer math)
    uint16_t distance = (duration * 343UL) / (2UL * 20000UL);

    return distance;
}

// ---- Main ----
int main(void) {
    DDRB |= (1 << BUZZER_PIN); // set buzzer pin as output
    UART_init(9600);
    Servo_init();
    Ultrasonic_init();

    while (1) {
        // Sweep forward
        for (uint8_t angle = 0; angle <= 180; angle++) {
            Servo_write(angle);
            _delay_ms(80); // slow and smooth sweep
            uint16_t dist = Ultrasonic_read();

            // UART output for Processing
            UART_print_num(angle);
            UART_transmit(',');
            UART_print_num(dist);
            UART_transmit('.');

            // Buzzer alert
            if (dist > 0 && dist < 30) {
                PORTB |= (1 << BUZZER_PIN); // buzzer ON
            } else {
                PORTB &= ~(1 << BUZZER_PIN); // buzzer OFF
            }
        }

        // Sweep backward
        for (uint8_t angle = 180; angle > 0; angle--) {
            Servo_write(angle);
            _delay_ms(80);
            uint16_t dist = Ultrasonic_read();

            UART_print_num(angle);
            UART_transmit(',');
            UART_print_num(dist);
            UART_transmit('.');

            if (dist > 0 && dist < 30) {
                PORTB |= (1 << BUZZER_PIN);
            } else {
                PORTB &= ~(1 << BUZZER_PIN);
            }
        }
    }
}