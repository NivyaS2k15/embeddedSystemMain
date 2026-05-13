#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// ---------------- ADC INIT ----------------
void adc_init()
{
	ADMUX = (1 << REFS0); // AVCC reference, ADC0

	ADCSRA = (1 << ADEN) |
	(1 << ADPS2) | (1 << ADPS1); // prescaler 64
}

// ---------------- ADC READ ----------------
uint16_t adc_read(uint8_t ch)
{
	ADMUX = (ADMUX & 0xF8) | ch; // select ADC channel

	ADCSRA |= (1 << ADSC);       // start conversion
	while (ADCSRA & (1 << ADSC));

	return ADC; // 10-bit value (0–1023)
}

// ---------------- PWM INIT (Timer0 Fast PWM) ----------------
void pwm_init()
{
	DDRD |= (1 << PD6); // OC0A output pin

	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM
	TCCR0B = (1 << CS01); // prescaler 8
}

// ---------------- SET SPEED ----------------
void motor_speed(uint8_t value)
{
	OCR0A = value; // 0–255 duty cycle
}

// ---------------- MAIN ----------------
int main(void)
{
	adc_init();
	pwm_init();

	uint16_t adc_value;
	uint8_t pwm_value;

	while (1)
	{
		// Read potentiometer (0–1023)
		adc_value = adc_read(0);

		// Scale to 8-bit PWM (0–255)
		pwm_value = adc_value / 4;

		// Apply speed
		motor_speed(pwm_value);

		_delay_ms(50);
	}
}