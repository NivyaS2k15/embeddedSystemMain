/*
 * UART_PWM_LED_CONTROL.c
 *
 * Created: 13-05-2026
 * Author : NIVYA
 */

#define F_CPU 16000000UL
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

/* ---------------- UART FUNCTIONS ---------------- */

void uart_char_transmit(char data)
{
	// Wait until transmit buffer becomes empty
	while (!(UCSR0A & (1 << UDRE0)));

	// Put data into buffer
	UDR0 = data;
}

void uart_String_transmit(const char* str)
{
	while (*str)
	{
		uart_char_transmit(*str);
		str++;
	}
}

char uart_receive_char()
{
	// Wait until data is received
	while (!(UCSR0A & (1 << RXC0)));

	return UDR0;
}

void uart_receive_string(char* buffer)
{
	char ch;
	int i = 0;

	while (1)
	{
		ch = uart_receive_char();

		// Enter key detection
		if (ch == '\r' || ch == '\n')
		{
			buffer[i] = '\0';
			return;
		}

		buffer[i] = ch;
		i++;

		// Prevent overflow
		if (i >= 19)
		{
			buffer[i] = '\0';
			return;
		}
	}
}

/* ---------------- PWM FUNCTIONS ---------------- */

void PWM_Init()
{
	// PD6 = OC0A output pin
	DDRD |= (1 << PD6);

	/*
	Timer0 Fast PWM Mode
	Non-Inverting Mode
	Prescaler = 64
	*/

	TCCR0A = (1 << COM0A1) |
	         (1 << WGM01)  |
	         (1 << WGM00);

	TCCR0B = (1 << CS01) | (1 << CS00);

	OCR0A = 0;
}

void PWM_SetBrightness(uint8_t brightness)
{
	// Convert percentage to 0-255
	OCR0A = (brightness * 255UL) / 100UL;
}

/* ---------------- MAIN FUNCTION ---------------- */

int main(void)
{
	char command[20];
	char message[50];
	int value;

	/* UART INITIALIZATION */

	UBRR0H = (UBRR_VALUE >> 8);
	UBRR0L = UBRR_VALUE;

	// Enable TX and RX
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);

	// 8-bit data, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	/* PWM INITIALIZATION */
	PWM_Init();

	uart_String_transmit("UART LED Control Ready\r\n");
	uart_String_transmit("Commands: ON, OFF, 0-100\r\n");

	while (1)
	{
		uart_receive_string(command);

		/* ---------- LED ON ---------- */

		if (strcmp(command, "ON") == 0)
		{
			PWM_SetBrightness(100);

			uart_String_transmit("LED is now ON\r\n");
		}

		/* ---------- LED OFF ---------- */

		else if (strcmp(command, "OFF") == 0)
		{
			PWM_SetBrightness(0);

			uart_String_transmit("LED is now OFF\r\n");
		}

		/* ---------- BRIGHTNESS CONTROL ---------- */

		else
		{
			value = atoi(command);

			if (value >= 0 && value <= 100)
			{
				PWM_SetBrightness(value);

				sprintf(message,
				        "Brightness set to %d%%\r\n",
				        value);

				uart_String_transmit(message);
			}
			else
			{
				uart_String_transmit("Invalid Command\r\n");
			}
		}
	}
}