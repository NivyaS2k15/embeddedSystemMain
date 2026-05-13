#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "i2c.h"
#include "lcd_i2c.h"
#include "bmp280.h"

int main(void)
{
	char buf[16];

	i2c_init();
	lcd_init();
	bmp280_init();

	lcd_clear();

	while (1)
	{
		float temp = bmp280_read_temp();

		lcd_clear();
		lcd_set_cursor(0, 0);
		lcd_print("TEMP:");

		sprintf(buf, "%.2f C", temp);

		lcd_set_cursor(1, 0);
		lcd_print(buf);

		_delay_ms(2000);
	}
}