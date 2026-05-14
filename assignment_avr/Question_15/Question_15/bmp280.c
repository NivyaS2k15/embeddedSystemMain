/*
 * bmp280.c
 */

#define F_CPU 16000000UL

#include "bmp280.h"
#include "i2c.h"

#include <util/delay.h>
#include <stdint.h>

// Calibration data
static uint16_t dig_T1;
static int16_t dig_T2, dig_T3;

static uint16_t dig_P1;
static int16_t dig_P2, dig_P3, dig_P4;
static int16_t dig_P5, dig_P6, dig_P7;
static int16_t dig_P8, dig_P9;

static int32_t t_fine;

// --------------------------------------------------
// WRITE REGISTER
// --------------------------------------------------
static void bmp_write(uint8_t reg, uint8_t data)
{
	i2c_start();

	i2c_write(BMP280_ADDR << 1);
	i2c_write(reg);
	i2c_write(data);

	i2c_stop();
}

// --------------------------------------------------
// READ 8-BIT REGISTER
// --------------------------------------------------
static uint8_t bmp_read8(uint8_t reg)
{
	uint8_t data;

	i2c_start();

	i2c_write(BMP280_ADDR << 1);
	i2c_write(reg);

	i2c_start();

	i2c_write((BMP280_ADDR << 1) | 1);

	data = i2c_read_nack();

	i2c_stop();

	return data;
}

// --------------------------------------------------
// READ 16-BIT REGISTER
// BMP280 sends LSB first, then MSB
// --------------------------------------------------
static uint16_t bmp_read16(uint8_t reg)
{
	uint8_t lsb, msb;

	i2c_start();

	i2c_write(BMP280_ADDR << 1);
	i2c_write(reg);

	i2c_start();

	i2c_write((BMP280_ADDR << 1) | 1);

	lsb = i2c_read_ack();
	msb = i2c_read_nack();

	i2c_stop();

	return ((uint16_t)msb << 8) | lsb;
}

// --------------------------------------------------
// INIT BMP280
// --------------------------------------------------
void bmp280_init(void)
{
	// Reset sensor
	bmp_write(0xE0, 0xB6);

	_delay_ms(100);

	// Read temperature calibration
	dig_T1 = bmp_read16(0x88);
	dig_T2 = (int16_t)bmp_read16(0x8A);
	dig_T3 = (int16_t)bmp_read16(0x8C);

	// Read pressure calibration
	dig_P1 = bmp_read16(0x8E);
	dig_P2 = (int16_t)bmp_read16(0x90);
	dig_P3 = (int16_t)bmp_read16(0x92);
	dig_P4 = (int16_t)bmp_read16(0x94);
	dig_P5 = (int16_t)bmp_read16(0x96);
	dig_P6 = (int16_t)bmp_read16(0x98);
	dig_P7 = (int16_t)bmp_read16(0x9A);
	dig_P8 = (int16_t)bmp_read16(0x9C);
	dig_P9 = (int16_t)bmp_read16(0x9E);

	// Normal mode
	// Temp oversampling x1
	// Pressure oversampling x1
	bmp_write(0xF4, 0x27);

	// Standby/config
	bmp_write(0xF5, 0x00);
}

// --------------------------------------------------
// READ TEMPERATURE
// --------------------------------------------------
float bmp280_read_temp(void)
{
	int32_t adc_T;

	adc_T  = ((uint32_t)bmp_read8(0xFA) << 12);
	adc_T |= ((uint32_t)bmp_read8(0xFB) << 4);
	adc_T |= (bmp_read8(0xFC) >> 4);

	int32_t var1, var2;

	var1 = ((((adc_T >> 3) -
	((int32_t)dig_T1 << 1))) *
	((int32_t)dig_T2)) >> 11;

	var2 = (((((adc_T >> 4) -
	((int32_t)dig_T1)) *
	((adc_T >> 4) -
	((int32_t)dig_T1))) >> 12) *
	((int32_t)dig_T3)) >> 14;

	t_fine = var1 + var2;

	float T = (t_fine * 5 + 128) >> 8;

	return T / 100.0;
}

// --------------------------------------------------
// READ PRESSURE
// --------------------------------------------------
float bmp280_read_pressure(void)
{
	int32_t adc_P;

	adc_P  = ((uint32_t)bmp_read8(0xF7) << 12);
	adc_P |= ((uint32_t)bmp_read8(0xF8) << 4);
	adc_P |= (bmp_read8(0xF9) >> 4);

	int64_t var1, var2, p;

	var1 = ((int64_t)t_fine) - 128000;

	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
	var2 = var2 + (((int64_t)dig_P4) << 35);

	var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) +
	((var1 * (int64_t)dig_P2) << 12);

	var1 = (((((int64_t)1) << 47) + var1) *
	((int64_t)dig_P1)) >> 33;

	if (var1 == 0)
	return 0;

	p = 1048576 - adc_P;

	p = (((p << 31) - var2) * 3125) / var1;

	var1 = (((int64_t)dig_P9) *
	(p >> 13) * (p >> 13)) >> 25;

	var2 = (((int64_t)dig_P8) * p) >> 19;

	p = ((p + var1 + var2) >> 8) +
	(((int64_t)dig_P7) << 4);

	return (float)p / 25600.0;
}