#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>





#define BUTTON_PIN PD2
#define MOTOR_PIN1 PD5   // OC0B
#define MOTOR_PIN2 PD6   // OC0A
#define LM35_CHANNEL 0   // ADC0

volatile uint8_t systemOn = 0;

// ---------- ADC INIT ----------
void ADC_Init(void) {
	ADMUX = (1<<REFS0); // AVcc reference, ADC0 channel
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable ADC, prescaler 64
}

uint16_t ADC_Read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC); // Start conversion
	while (ADCSRA & (1<<ADSC)); // Wait
	return ADC;
}

// ---------- TIMER0 PWM INIT ----------
void PWM_Init(void) {
	DDRD |= (1<<MOTOR_PIN1) | (1<<MOTOR_PIN2); // PD5, PD6 outputs
	TCCR0A = (1<<COM0A1) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01); // Fast PWM
	TCCR0B = (1<<CS01); // Prescaler 8
}

// ---------- BUTTON INTERRUPT ----------
void Button_Init(void) {
	DDRD &= ~(1<<BUTTON_PIN); // Input
	PORTD |= (1<<BUTTON_PIN); // Pull-up
	EICRA |= (1<<ISC01);      // Falling edge INT0
	EIMSK |= (1<<INT0);       // Enable INT0
	sei();                    // Global interrupt enable
}

ISR(INT0_vect) {
	systemOn ^= 1; // Toggle system state
}

// ---------- TEMPERATURE READ ----------
float readTemperature(void) {
	uint16_t adcVal = ADC_Read(LM35_CHANNEL);
	float voltage = (adcVal * 5.0) / 1024.0;
	return voltage * 100.0; // LM35: 10mV/°C
}

// ---------- SPEED CALCULATION ----------
uint8_t calculateSpeed(float temp) {
	if (temp < 30) return 100;
	else if (temp < 40) return 150;
	else return 255;
}

// ---------- MOTOR CONTROL ----------
void controlMotor(uint8_t speed) {
	OCR0A = speed; // PD6
	OCR0B = 0;     // PD5 low (one direction)
}

// ---------- MAIN ----------
int main(void) {
	ADC_Init();
	PWM_Init();
	Button_Init();

	while (1) {
		if (systemOn) {
			float temp = readTemperature();
			uint8_t speed = calculateSpeed(temp);
			controlMotor(speed);
			} else {
			controlMotor(0); // Motor OFF
		}
		_delay_ms(200);
	}
}

