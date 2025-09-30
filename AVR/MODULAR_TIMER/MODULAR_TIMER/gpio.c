/*
 * gpio.c
 *
 * Created: 30-09-2025 21:12:16
 *  Author: NIVYA
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void pin_initialization(void){
	 DDRD |= (1<<DDD0) | (1<<DDD1) | (1<<DDD2) | (1<<DDD3) | (1<<DDD4);
}