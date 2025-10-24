/*
 * UART_FIRST.c
 *
 * Created: 24-10-2025 16:16:33
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/delay.h>
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)  // UBRR = 103


 void uart_char_transmit(char data) {
	 // Wait until transmit buffer is empty (UDRE0 = 1)
	 while (!(UCSR0A & (1 << UDRE0)));

	 // Load data into transmit buffer
	 UDR0 = data;
 }

void uart_String_transmit(const char* str) {
	while (*str) {
		uart_char_transmit(*str);  // Send each character
		str++;                     // Move to next character
	}
}

int main(void)
{
	UBRR0H = (UBRR_VALUE>>8); //right shift to make this 
	UBRR0L =UBRR_VALUE;
	
     // Enable transmitter
     UCSR0B = (1 << TXEN0);
	  // Set frame format: 8 data bits, 1 stop bit, no parity
	  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Bits 1 and 0 of UCSR0C

	
	
	
    /* Replace with your application code */
    while (1) 
    {
		uart_String_transmit("helo world nivya");
		  // pasing string 
		  _delay_ms(1000)  ;
		  uart_char_transmit('\n');  
		uart_char_transmit('D');  // passing character
	
		_delay_ms(1000)  ;// one second wait
		 uart_char_transmit('\n'); 
    }
}

