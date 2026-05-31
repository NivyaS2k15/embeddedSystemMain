///*
// * main_button_toggle.c
// *
// *  Created on: May 28, 2026
// *      Author: NIVYA
// */
//
//
///**
// ******************************************************************************
// * @file           : main_button_toggle.c
// * @brief          : Application 1: Robust Button Debounce and LED Toggle
// ******************************************************************************
// */
//
//#include "stm32f446xx.h"
//#include "stm32f446xx_gpio_driver.h"
//
//void delay_debounce(void)
//{
//    // Software delay loop for ~20ms debounce timing
//    for(uint32_t i = 0; i < 40000; i++);
//}
//
//int main(void)
//{
//    GPIO_Handle_t GpioLed, GpioBtn;
//
//    /* Onboard LED configuration: PA5 */
//    GpioLed.pGPIOx = GPIOA;
//    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
//    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
//    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
//    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
//
//    GPIO_PeriClockControl(GPIOA, ENABLE);
//    GPIO_Init(&GpioLed);
//
//    /* User Button configuration: PA9 */
//    GpioBtn.pGPIOx = GPIOA;
//    GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
//    GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
//    GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//    GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; // Pull-up active
//
//    GPIO_Init(&GpioBtn);
//
//    while(1)
//    {
//        // Condition: PA9 goes LOW when the button is pressed
//        if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_9) == 0)
//        {
//            // Step 1: Wait out initial mechanical bounce (Press-bounce)
//            delay_debounce();
//
//            // Step 2: Execute the state change
//            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
//
//            // Step 3: Wait here as long as the user holds the button down
//            while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_9) == 0);
//
//            // Step 4: Wait out the mechanical release bounce (Break-bounce)
//            delay_debounce();
//        }
//    }
//}
