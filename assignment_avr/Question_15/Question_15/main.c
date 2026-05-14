#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "i2c.h"
#include "lcd_i2c.h"
#include "bmp280.h"

int main(void)
{
	char buf[20];

	i2c_init();

	lcd_init();

	bmp280_init();

	lcd_clear();

	while (1)
	{
		float temp;
		float press;

		temp = bmp280_read_temp();

		press = bmp280_read_pressure();

		lcd_clear();

		// TEMPERATURE
		lcd_set_cursor(0, 0);

		lcd_print("T:");

		dtostrf(temp, 6, 2, buf);

		lcd_print(buf);

		lcd_print("C");

		// PRESSURE
		lcd_set_cursor(1, 0);

		lcd_print("P:");

		dtostrf(press, 7, 2, buf);

		lcd_print(buf);

		lcd_print("hPa");

		_delay_ms(2000);
	}
}