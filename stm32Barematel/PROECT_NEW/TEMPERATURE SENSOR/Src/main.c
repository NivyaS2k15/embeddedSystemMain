/*
 * main.c
 * Target: Analog Temperature Sensor Engine
 * Peripherals: ADC1 (PA1) + I2C1 LCD (PB8/PB9) + USART2 (PA2/PA3)
 */

#include <stdio.h>
#include <string.h>
#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_usart_driver.h"
#include "stm32f446xx_i2c_driver.h"
#include "stm32f446xx_rcc_driver.h"
#include "i2c_lcd.h"

#define GPIO_PIN_NO_8         8 // PB8 -> I2C1_SCL
#define GPIO_PIN_NO_9         9 // PB9 -> I2C1_SDA

USART_Handle_t usart2_handle;
I2C_Handle_t   i2c1_handle;

void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < (ms * 1000); i++);
}

void USART2_GPIOInit(void)
{
    GPIO_Handle_t usart_gpios = {0};
    usart_gpios.pGPIOx = GPIOA;
    usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

    usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2; // TX
    GPIO_Init(&usart_gpios);
    usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3; // RX
    GPIO_Init(&usart_gpios);
}

void USART2_Init(void)
{
    usart2_handle.pUSARTx = USART2;
    usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
    usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
    usart2_handle.USART_Config.USART_Mode = USART_MODE_TXRX;
    usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    USART_Init(&usart2_handle);
}

void I2C1_GPIOInit(void)
{
    GPIO_Handle_t i2c_gpios = {0};
    i2c_gpios.pGPIOx = GPIOB;
    i2c_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    i2c_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
    i2c_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    i2c_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    i2c_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = 4;

    i2c_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIO_Init(&i2c_gpios);
    i2c_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&i2c_gpios);
}

void I2C1_Init(void)
{
    I2C_PeriClockControl(I2C1, ENABLE);
    RCC->APB1RSTR |=  (1 << 21);
    delay_ms(10);
    RCC->APB1RSTR &= ~(1 << 21);
    delay_ms(10);

    i2c1_handle.pI2Cx = I2C1;
    i2c1_handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;
    i2c1_handle.I2C_Config.I2C_DeviceAddress = 0x20;
    i2c1_handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
    I2C_Init(&i2c1_handle);
}

/* * Initialize PA1 as an Analog Input for ADC1_IN1
 */
void ADC1_CH1_GPIOInit(void)
{
    GPIO_Handle_t adc_pin = {0};
    adc_pin.pGPIOx = GPIOA;
    adc_pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    adc_pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ANALOG; // Explicit Analog Mode
    adc_pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&adc_pin);
}

/* * Setup the internal ADC1 Hardware Engine
 */
void ADC1_Init(void)
{
    // 1. Enable ADC1 Clock in RCC
    RCC->APB2ENR |= (1 << 8);

    // 2. Set Sequencer Length to 1 conversion (ADC_SQR1 bits [23:20] = 0000)
    ADC1->SQR1 &= ~(0xF << 20);

    // 3. Assign Channel 1 as the 1st conversion sequence spot (ADC_SQR3 bits [4:0] = 00001)
    ADC1->SQR3 &= ~(0x1F << 0);
    ADC1->SQR3 |=  (1 << 0);

    // 4. Power up the ADC peripheral (Set ADON bit in CR2)
    ADC1->CR2 |= (1 << 0);
}

/*
 * Fire a conversion and poll the register status for the result data
 */
uint32_t ADC1_Read(void)
{
    // Start Conversion (SWSTART bit in CR2)
    ADC1->CR2 |= (1 << 30);

    // Poll for End of Conversion (EOC bit in SR)
    while (!(ADC1->SR & (1 << 1)));

    // Return the converted 12-bit digital value
    return ADC1->DR;
}

int main(void)
{
    char log_buffer[64];
    char lcd_buffer[16];

    // Enable Peripheral Clocks
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    // Communications Setup
    USART2_GPIOInit();
    USART2_Init();
    USART_PeripheralControl(USART2, ENABLE);

    I2C1_GPIOInit();
    GPIOB->AFR[1] &= ~( (0xFU << 0) | (0xFU << 4) );
    GPIOB->AFR[1] |=  ( (0x4U << 0) | (0x4U << 4) );
    I2C1_Init();
    I2C_PeripheralControl(I2C1, ENABLE);
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

    // Display Setup - Removed "LM35" text prefix here
    LCD_Init(&i2c1_handle);
    LCD_Clear(&i2c1_handle);
    LCD_SetCursor(&i2c1_handle, 0, 0);
    LCD_SendString(&i2c1_handle, "TEMP MONITOR");

    // Analog Infrastructure Setup
    ADC1_CH1_GPIOInit();
    ADC1_Init();

    while(1)
    {
        // 1. Fetch raw value from ADC (Range: 0 to 4095)
        uint32_t raw_adc = ADC1_Read();

        // 2. Math Processing
        uint32_t temp_scaled = (raw_adc * 330000) / 40950;

        uint32_t integer_part = temp_scaled / 100;
        uint32_t fractional_part = temp_scaled % 100;

        /* --- 3. Transmit Raw Driver Call over USART2 - Removed "LM35" tag --- */
        sprintf(log_buffer, "[UPDATE]: Temp = %ld.%02ld C\r\n", integer_part, fractional_part);
        USART_SendData(&usart2_handle, (uint8_t*)log_buffer, strlen(log_buffer));

        /* --- 4. Update the LCD Screen Layout --- */
        sprintf(lcd_buffer, "Temp: %ld.%02ld C   ", integer_part, fractional_part);
        LCD_SetCursor(&i2c1_handle, 1, 0);
        LCD_SendString(&i2c1_handle, lcd_buffer);

        delay_ms(1000);
    }

    return 0;
}
