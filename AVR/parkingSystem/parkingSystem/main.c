/*
 * main.c – AVR Car Parking Project (fixed pulseIn)
 * Target: ATmega328P (Arduino Uno chip)
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"

/* ---------------- CONFIG ---------------- */
#define TOTAL_SLOTS        4
#define DIST_THRESHOLD     10   // cm

/* Ultrasonic pins (PORTC) */
#define TRIG1 PC0   // A0
#define ECHO1 PC1   // A1
#define TRIG2 PC2   // A2
#define ECHO2 PC3   // A3

/* Servo pin (OC1A on PB1 = Arduino D9) */
#define SERVO_PIN PB1

/* ---------------- GLOBALS ---------------- */
uint8_t Slot = TOTAL_SLOTS;
uint8_t flag1 = 0, flag2 = 0;

/* ---------------- SERVO (Timer1 PWM) ---------------- */
void servo_init(void)
{
    DDRB |= (1 << SERVO_PIN); // PB1 output

    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // prescaler 8
    ICR1 = 20000;   // 20ms period (16MHz/8 = 2MHz ? 0.5us per tick)
}

void servo_write(uint8_t angle)
{
    // 1ms–2ms pulse ? 2000–4000 counts
    uint16_t pulse = 2000 + ((uint32_t)angle * 2000) / 180;
    OCR1A = pulse;
}

/* ---------------- Arduino-style pulseIn (live PIN reads) ---------------- */
uint32_t pulseInC(uint8_t pinMask)
{
    uint32_t count = 0;

    // 1) Wait for any previous HIGH to finish (go LOW)
    uint32_t timeout = 30000;
    while (PINC & pinMask) {
        if (--timeout == 0) return 0;
        _delay_us(1);
    }

    // 2) Wait for rising edge (LOW -> HIGH)
    timeout = 30000;
    while (!(PINC & pinMask)) {
        if (--timeout == 0) return 0;
        _delay_us(1);
    }

    // 3) Measure HIGH duration in microseconds
    count = 0;
    timeout = 60000; // cap ~60ms to avoid hang
    while (PINC & pinMask) {
        _delay_us(1);
        count++;
        if (--timeout == 0) break;
    }

    return count; // microseconds
}

/* ---------------- ULTRASONIC ---------------- */
uint16_t getDistance(uint8_t trigPin, uint8_t echoPin)
{
    // Ensure TRIG idle low
    PORTC &= ~(1 << trigPin);
    _delay_us(2);

    // Trigger pulse (10us)
    PORTC |= (1 << trigPin);
    _delay_us(10);
    PORTC &= ~(1 << trigPin);

    // Measure echo pulse width
    uint32_t duration_us = pulseInC((uint8_t)(1 << echoPin));
    if (duration_us == 0) return 0xFFFF; // timeout/no echo

    // Convert to cm: distance = (duration_us * 0.034) / 2
    return (uint16_t)((duration_us * 34UL) / 2000UL); // integer math ? duration*0.017
}

/* ---------------- MAIN ---------------- */
int main(void)
{
    /* LCD */
    lcd_init();

    /* Ultrasonic pins */
    DDRC |= (1 << TRIG1) | (1 << TRIG2);           // TRIG outputs
    DDRC &= ~((1 << ECHO1) | (1 << ECHO2));        // ECHO inputs
    PORTC &= ~((1 << TRIG1) | (1 << TRIG2));       // TRIG idle low
    // No pull-ups on echo lines:
    PORTC &= ~((1 << ECHO1) | (1 << ECHO2));

    /* Servo */
    servo_init();
    servo_write(100);   // closed

    /* Welcome screen */
    lcd_set_cursor(0, 0);
    lcd_print("    ARDUINO    ");
    lcd_set_cursor(1, 0);
    lcd_print(" PARKING SYSTEM ");
    _delay_ms(2000);
    lcd_clear();

    uint8_t lastSlot = 255;

    while (1)
    {
        uint16_t d1 = getDistance(TRIG1, ECHO1);
        uint16_t d2 = getDistance(TRIG2, ECHO2);

        /* ENTRY */
        if (d1 != 0xFFFF && d1 < DIST_THRESHOLD && flag1 == 0) {
            if (Slot > 0) {
                flag1 = 1;
                servo_write(0);   // open gate
                Slot--;
            } else {
                lcd_clear();
                lcd_set_cursor(0, 0);
                lcd_print("    SORRY :(    ");
                lcd_set_cursor(1, 0);
                lcd_print("  Parking Full  ");
                _delay_ms(3000);
                lcd_clear();
            }
        }

        /* EXIT */
        if (d2 != 0xFFFF && d2 < DIST_THRESHOLD && flag2 == 0) {
            flag2 = 1;
            servo_write(0);   // open gate
            if (Slot < TOTAL_SLOTS) Slot++;
        }

        /* RESET GATE */
        if (flag1 || flag2) {
            _delay_ms(3000);
            servo_write(100); // close gate
            flag1 = 0;
            flag2 = 0;
        }

        /* LCD UPDATE ONLY ON CHANGE */
        if (Slot != lastSlot) {
            lcd_clear();
            lcd_set_cursor(0, 0);
            lcd_print("    WELCOME!    ");
            lcd_set_cursor(1, 0);
            lcd_print("Slot Left: ");
            lcd_print_uint16(Slot);
            lastSlot = Slot;
        }

        _delay_ms(200);
    }
}