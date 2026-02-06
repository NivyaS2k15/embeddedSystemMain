#ifndef TM1637_H_
#define TM1637_H_

#include "stm32f446xx_gpio_driver.h"

// Pin selection (change pins here if needed)
#define TM1637_CLK_PORT   GPIOA
#define TM1637_CLK_PIN    GPIO_PIN_NO_6

#define TM1637_DIO_PORT   GPIOA
#define TM1637_DIO_PIN    GPIO_PIN_NO_7


void TM1637_Init(void);
void TM1637_DisplayTime(uint8_t hour, uint8_t min);

#endif
