#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#define BUTTON_PIN PD2
#define MOTOR_PIN PD6
#define LM35_CHANNEL 0

volatile bool systemOn = false;

// ---------- Function Prototypes ----------
void init_ADC(void);
uint16_t read_ADC(uint8_t channel);
float readTemperature(void);
uint8_t calculateSpeed(float temp);
void controlMotor(uint8_t duty);
void init_PWM(void);
void init_Button(void);

// ---------- Main ----------
int main(void) {
	init_ADC();
	init_PWM();
	init_Button();
	sei(); // Enable global interrupts

	while (1) {
		if(systemOn) {
			float temp = readTemperature();
			uint8_t speed = calculateSpeed(temp);
			controlMotor(speed);
			} else {
			controlMotor(0); // Motor OFF
		}
	}
}

// ---------- Button Interrupt ----------
ISR(INT0_vect) {
	systemOn = !systemOn; // Toggle system state
}

// ---------- ADC Init ----------
void init_ADC(void) {
	ADMUX = (1<<REFS0); // AVcc reference
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1); // Enable ADC, prescaler 64
}

// ---------- ADC Read ----------
uint16_t read_ADC(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select channel
	ADCSRA |= (1<<ADSC); // Start conversion
	while(ADCSRA & (1<<ADSC)); // Wait
	return ADC;
}

// ---------- Temperature Read ----------
float readTemperature(void) {
	uint16_t adcValue = read_ADC(LM35_CHANNEL);
	// LM35: 10mV/°C, ADC step = 4.88mV (for 5V, 10-bit)
	return (adcValue * 5.0 * 100.0) / 1024.0;
}

// ---------- Speed Calculation ----------
uint8_t calculateSpeed(float temp) {
	if(temp < 30) return 77;     // ~30% duty
	else if(temp < 50) return 153; // ~60% duty
	else return 230;             // ~90% duty
}

// ---------- Motor Control ----------
void controlMotor(uint8_t duty) {
	OCR0A = duty; // Set PWM duty cycle
}

// ---------- PWM Init ----------
void init_PWM(void) {
	DDRD |= (1<<MOTOR_PIN); // PD6 as output
	TCCR0A = (1<<COM0A1) | (1<<WGM00) | (1<<WGM01); // Fast PWM, non-inverting
	TCCR0B = (1<<CS01); // Prescaler = 8
}

// ---------- Button Init ----------
void init_Button(void) {
	DDRD &= ~(1<<BUTTON_PIN); // PD2 as input
	PORTD |= (1<<BUTTON_PIN); // Enable pull-up
	EICRA |= (1<<ISC01); // Falling edge INT0
	EIMSK |= (1<<INT0);  // Enable INT0
}
