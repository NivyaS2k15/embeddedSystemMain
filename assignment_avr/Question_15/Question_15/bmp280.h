#ifndef BMP280_H_
#define BMP280_H_

#include <avr/io.h>

#define BMP280_ADDR 0x76   // change to 0x77 if your module uses that address

void bmp280_init(void);
float bmp280_read_temp(void);
float bmp280_read_pressure(void);

#endif /* BMP280_H_ */
