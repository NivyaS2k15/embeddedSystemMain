/*
 * Question_11.c
 *
 * Created: 13-05-2026 13:09:50
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// ---------------- ADC ----------------
void adc_init()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t adc_read(uint8_t ch)
{
	ADMUX = (ADMUX & 0xF8) | ch;

	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));

	return ADC;
}

// ---------------- SERVO INIT ----------------
void servo_init()
{
	DDRB |= (1 << PB1);

	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << CS11);

	ICR1 = 40000; // 20ms
}

// ---------------- BETTER SERVO MAPPING ----------------
void servo_write(uint16_t adc)
{
	// better calibrated range (important FIX)
	uint16_t pulse = 600 + ((uint32_t)adc * 1800) / 1023;

	OCR1A = pulse * 2;
}

// ---------------- SIMPLE FILTER ----------------
uint16_t smooth_adc(uint8_t ch)
{
	uint32_t sum = 0;

	for (int i = 0; i < 5; i++)
	{
		sum += adc_read(ch);
		_delay_ms(2);
	}

	return sum / 5;
}

// ---------------- MAIN ----------------
int main(void)
{
	adc_init();
	servo_init();

	while (1)
	{
		uint16_t adc_val = smooth_adc(0);

		servo_write(adc_val);

		_delay_ms(15); // faster update = smoother sync
	}
}