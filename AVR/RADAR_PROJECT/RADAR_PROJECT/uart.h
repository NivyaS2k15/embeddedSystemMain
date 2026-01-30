/*
 * uart.h
 *
 * Created: 19-01-2026 12:38:19
 *  Author: NIVYA
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_init(unsigned long baud);
void UART_transmit(unsigned char data);
void UART_print(const char *str);
void UART_print_num(uint16_t num);

#endif /* UART_H_ */