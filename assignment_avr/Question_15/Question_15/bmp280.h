#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>

void bmp280_init(void);
float bmp280_read_temp(void);

#endif