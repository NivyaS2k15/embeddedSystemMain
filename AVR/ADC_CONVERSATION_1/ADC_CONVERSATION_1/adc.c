/*
 * adc.c
 *
 * Created: 23-10-2025 17:12:47
 *  Author: NIVYA
 */ 
#define F_CPU 16000000UL
#include "adc.h"

void adc_init(void){
 ADMUX |=(1<<REFS0)	;  // ENABLE VCC 5V
 ADCSRA |=(1<<ADEN); // SET ENABLE = 1 
 
 ADCSRA |=(1<<ADPS0);
  ADCSRA |=(1<<ADPS1);
   
 ADCSRA |=(1<<ADPS2); // ENABLE 128 PRESCALAR  16000000/128 = 125KHZ
 
}
 uint16_t adc_read(uint8_t channel){
	 
 
   channel &= 0x7; // limit the channel to o=7
   ADMUX =(ADMUX & 0xF8) | channel ; // DELECT CHANNEL
   ADCSRA |=(1<<ADSC);//START CONVERSATION
   while(ADCSRA & (1<<ADSC));  // convert untill the zero  
   return  (ADCL |(ADCH <<8)); // shift the adh to 8 times then or with adcl we get 16 bit
   
 
} 