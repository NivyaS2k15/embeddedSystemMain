/*
 * adc_temperator_sensor.c
 *
 * Created: 23-10-2025 20:41:24
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"



void ADC_Init(void)     // ADC Initialisation
{
	ADMUX |= (1 << REFS0); // Reference = AVCC (5V), input = ADC0
	ADCSRA |= (1 << ADEN)| (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC. Prescaler = 128(125 kHz ADC clock)
}

uint16_t ADC_Read(uint8_t channel)   // ADC reading
{
	channel &= 0x07;                     // Limit to 0–7
	ADMUX = (ADMUX & 0xF8) | channel;    // Select channel
	ADCSRA |= (1 << ADSC);               // Start conversion
	while (ADCSRA & (1 << ADSC));        // Wait for conversion complete
	return (ADCL | (ADCH << 8));         // Combine result
}

int main(void)
{
	uint16_t adc_value;
	lcd_init();
	ADC_Init();   // call ADC initialisation function
	while (1)
	{
		float temp;
		lcd_clear();
		lcd_set_cursor(0,0);
		lcd_print("Temperature Area:");
		
		adc_value = ADC_Read(2);// Read from analog channel 0 (A0 pin of arduino)
		temp= adc_value*0.488;  // Converting adc value into temperature
		lcd_set_cursor(1,0);
		  // printing temperature
	    lcd_print_float(temp);
		lcd_data(0xDF);      // To print degree symbol(came from the data sheet of lcd controller )
		lcd_print("C");
		_delay_ms(500);
	}
}