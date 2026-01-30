/*
 * uart.c
 *
 * Created: 19-01-2026 12:39:02
 *  Author: NIVYA
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

#include "uart.h"
#include <stdlib.h>

void UART_init(unsigned long baud) {
	unsigned int ubrr = (F_CPU / 16 / baud) - 1;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);                       // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);      // 8-bit data, 1 stop bit
}

void UART_transmit(unsigned char data) {
	while (!(UCSR0A & (1 << UDRE0)));            // Wait for empty buffer
	UDR0 = data;
}

void UART_print(const char *str) {
	while (*str) {
		UART_transmit(*str++);
	}
}

void UART_print_num(uint16_t num) {
	char buffer[10];
	itoa(num, buffer, 10);
	UART_print(buffer);
}