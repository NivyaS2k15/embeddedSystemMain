#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "lcd.h"

// Button on PB0
#define BUTTON_PIN PB0

uint32_t counter = 0;

// ---------------- LCD PRINT 9 DIGITS ----------------
void lcd_print_9digit(uint32_t num)
{
	char digits[10];
	digits[9] = '\0';

	for (int i = 8; i >= 0; i--)
	{
		digits[i] = (num % 10) + '0';
		num /= 10;
	}

	lcd_set_cursor(0, 0);
	lcd_print(digits);
}

// ---------------- BUTTON CHECK ----------------
uint8_t check_button_press()
{
	uint16_t hold_time = 0;

	// wait for press (active low assumed)
	if (PINB & (1 << BUTTON_PIN))
	return 0;

	_delay_ms(20); // debounce

	while (!(PINB & (1 << BUTTON_PIN)))
	{
		_delay_ms(10);
		hold_time += 10;

		if (hold_time >= 2000)
		{
			// wait for release
			while (!(PINB & (1 << BUTTON_PIN)));
			_delay_ms(20);
			return 2; // long press
		}
	}

	_delay_ms(20);
	return 1; // short press
}

// ---------------- MAIN ----------------
int main(void)
{
	// Button input with pull-up
	DDRB &= ~(1 << BUTTON_PIN);
	PORTB |= (1 << BUTTON_PIN);

	lcd_init();
	lcd_clear();

	lcd_set_cursor(0, 0);
	lcd_print("000000000");

	while (1)
	{
		uint8_t press = check_button_press();

		if (press == 1)
		{
			counter++;
			if (counter > 999999999)
			counter = 0;

			lcd_print_9digit(counter);
		}
		else if (press == 2)
		{
			counter = 0;
			lcd_print_9digit(counter);
		}
	}
}