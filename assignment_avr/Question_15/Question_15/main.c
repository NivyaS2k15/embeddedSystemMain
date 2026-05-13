#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "i2c.h"
#include "lcd_i2c.h"
#include "bmp280.h"

int main(void)
{
	char buf[20];

	// initialize I2C, LCD, and BMP280
	i2c_init();
	lcd_init();
	bmp280_init();

	lcd_clear();

	while (1)
	{
		float temp = bmp280_read_temp();       // °C
		float press = bmp280_read_pressure();  // hPa

		lcd_clear();

		// show temperature
		lcd_set_cursor(0, 0);
		sprintf(buf, "T: %.2f C", temp);
		lcd_print(buf);

		// show pressure
		lcd_set_cursor(1, 0);
		sprintf(buf, "P: %.2f hPa", press);
		lcd_print(buf);

		_delay_ms(2000); // update every 2 seconds
	}
}
