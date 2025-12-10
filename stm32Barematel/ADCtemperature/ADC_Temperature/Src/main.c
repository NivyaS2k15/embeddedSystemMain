




/**
 ******************************************************************************
 * @file           : main.c
 * @author         : NIVYA S
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "stm32f446xx.h"
#include <stdio.h>
#include <stdint.h>

void ADC1_Init(void) {
    ADC1_CLK_EN();
    GPIOA_CLK_EN();

    GPIOA->MODER &= ~(0x3 << (2 * 2)); //channel pa2
    GPIOA->MODER |=  (0x3 << (2 * 2));

    ADC1->SQR3 = 2; //channel 2
    ADC1->SQR1 = 0;

    ADC1->CR2 |= (0x1 << 0);     // ADON
}

uint16_t ADC1_Read(void) {
    ADC1->CR2 |= (1 << 30);          // SWSTART
    while (!(ADC1->SR & (1 << 1)));  // EOC
    return ADC1->DR;
}

static inline unsigned int adc_to_milli_celsius(uint16_t adc_raw) {
    const unsigned int VREF_mV = 3300U;
    const unsigned int ADC_RES = 4096U;
    return (unsigned int)(((uint32_t)adc_raw * VREF_mV * 1000U) / (ADC_RES * 10U));
}

int main(void) {
    int calib_offset_mC = -34060;  // Adjust to match 27 °C

    ADC1_Init();

    while (1) {
        uint32_t sum = 0;
        for (int i = 0; i < 16; i++) {
            sum += ADC1_Read();
        }
        uint16_t adc = (uint16_t)(sum / 16U);

        unsigned int temp_mC = adc_to_milli_celsius(adc);
        int temp_mC_cal = (int)temp_mC + calib_offset_mC;
       // printf("ADC raw: %u \n",adc);
        printf("Temperature: %d.%02u °C\n",

               temp_mC_cal / 1000,
               (unsigned)((unsigned)(temp_mC_cal % 1000) / 10U));

        for (volatile int i = 0; i < 1000000; i++);
    }
}
