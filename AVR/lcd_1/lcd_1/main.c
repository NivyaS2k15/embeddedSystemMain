/*
 * lcd_1.c
 *
 * Created: 21-10-2025 17:32:49
 * Author : NIVYA
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	lcd_init();


	// small demo: print a number
	//lcd_print_uint16(1234);

	while (1)
	{
			lcd_set_cursor(0, 0);
		    lcd_print("Hello NIVYA");

			lcd_set_cursor(1, 0);
			lcd_print("It works! ");
			_delay_ms(1000);
			  lcd_clear();
		    lcd_print_uint16(1203);
		       _delay_ms(1000);
		      lcd_clear();
		_delay_ms(1000);
	    lcd_print_float(33.75);
		_delay_ms(1000);
		lcd_clear();
		_delay_ms(1000);

	}
}


