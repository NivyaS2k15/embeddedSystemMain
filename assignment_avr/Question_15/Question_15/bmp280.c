#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "bmp280.h"

#define BMP280_ADDR 0x76

#define REG_TEMP_MSB 0xFA
#define REG_CTRL_MEAS 0xF4

static void bmp_write(uint8_t reg, uint8_t data)
{
	i2c_start();
	i2c_write(BMP280_ADDR << 1);
	i2c_write(reg);
	i2c_write(data);
	i2c_stop();
}

static uint8_t bmp_read8(uint8_t reg)
{
	uint8_t data;

	i2c_start();
	i2c_write(BMP280_ADDR << 1);
	i2c_write(reg);

	i2c_start();
	i2c_write((BMP280_ADDR << 1) | 1);

	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));

	data = TWDR;
	i2c_stop();

	return data;
}

void bmp280_init(void)
{
	bmp_write(REG_CTRL_MEAS, 0x27); // temp enable
	_delay_ms(100);
}

float bmp280_read_temp(void)
{
	uint8_t msb = bmp_read8(REG_TEMP_MSB);
	uint8_t lsb = bmp_read8(REG_TEMP_MSB + 1);
	uint8_t xlsb = bmp_read8(REG_TEMP_MSB + 2);

	int32_t raw = ((int32_t)msb << 12) |
	((int32_t)lsb << 4) |
	(xlsb >> 4);

	// simplified conversion
	float temp = (raw / 16384.0) * 165.0 - 40.0;

	return temp;
}