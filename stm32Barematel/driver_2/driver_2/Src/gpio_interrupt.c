/*
 * gpio_interrupt.c
 *
 *  Created on: Feb 20, 2026
 *      Author: NIVYA
 */


#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"

void delay1(void)
{
    for(uint32_t i = 0; i < 500000; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed, GpioIntr;

    /* configurations for LED */
    GpioLed.pGPIOx = GPIOA;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOA, ENABLE);

    GPIO_Init(&GpioLed);

    GpioIntr.pGPIOx = GPIOC;
    GpioIntr.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GpioIntr.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;   // Interrupt on falling edge
    GpioIntr.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioIntr.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    GPIO_PeriClockControl(GPIOC, ENABLE);

    GPIO_Init(&GpioIntr);

    GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
  while(1);

}
void EXTI15_10_IRQHandler(void)
{
    GPIO_IRQHandling(GPIO_PIN_NO_13);              // Clear the interrupt flag for pin 13
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);   // Toggle LED on PA5
}

