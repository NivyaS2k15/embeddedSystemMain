/*
 * main_software_pwm.c
 *
 *  Created on: May 28, 2026
 *      Author: NIVYA
 */


/**
 ******************************************************************************
 * @file           : main_software_pwm.c
 * @brief          : Application 2: Software Timing Based PWM LED Fading
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"

// Basic timing delay loop
void delay_cycles(uint32_t count)
{
    for(uint32_t i = 0; i < count; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed;

    /* LED configuration: PA5 */
    GpioLed.pGPIOx = GPIOA;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_Init(&GpioLed);

    uint32_t period = 400;  // Total software PWM cycle period window
    uint32_t duty_cycle = 0;// Starting duty cycle (0% brightness)
    int8_t fade_direction = 4; // Step size for fading speed

    while(1)
    {
        /* --- PWM Pulse Generation Loop --- */
        // We repeat each duty cycle state 25 times so the human eye can register the brightness
        for(int frame = 0; frame < 25; frame++)
        {
            // If duty cycle is greater than 0, turn LED ON for the calculated duration
            if(duty_cycle > 0)
            {
                GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);
                delay_cycles(duty_cycle);
            }

            // Turn LED OFF for the remaining duration of the period
            if(duty_cycle < period)
            {
                GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET);
                delay_cycles(period - duty_cycle);
            }
        }

        /* --- Brightness Modulation Logic --- */
        duty_cycle += fade_direction;

        // Reverse fade direction if maximum or minimum thresholds are reached
        if(duty_cycle >= period)
        {
            duty_cycle = period;
            fade_direction = -fade_direction; // Start fading down
        }
        else if(duty_cycle <= 0)
        {
            duty_cycle = 0;
            fade_direction = -fade_direction; // Start fading up
        }
    }
}
