/*
 * main.c
 * Target: LM75 Digital Temperature Sensor Engine
 * Peripherals: I2C1 (PB8/PB9 Shared: LCD + LM75) + USART2 (PA2/PA3)
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

#define LM75_TEMP_REG        0x00
#define LM75_SLAVE_ADDR      0x48

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

/*
 * Reads 2 bytes from the LM75 to capture the fractional component.
 */
void LM75_ReadTempRaw(int16_t *raw_temp)
{
    uint8_t reg_addr = LM75_TEMP_REG;
    uint8_t buffer[2] = {0};

    // 1. Send register pointer address
    I2C_MasterSendData(&i2c1_handle, &reg_addr, 1, LM75_SLAVE_ADDR, I2C_DISABLE_SR);

    // Microsecond line stabilization delay
    for(volatile uint32_t i = 0; i < 1000; i++);

    // 2. Read 2 bytes back from the device to get full resolution
    I2C_MasterReceiveData(&i2c1_handle, buffer, 2, LM75_SLAVE_ADDR, I2C_DISABLE_SR);

    // Combine MSB and LSB into a 16-bit signed integer
    *raw_temp = (int16_t)((buffer[0] << 8) | buffer[1]);
}

int main(void)
{
    char log_buffer[64];
    char lcd_buffer[16];
    int16_t raw_temp = 0;

    // Enable Peripheral Clocks
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    // Communications Setup: USART2 first so we can track initialization status
    USART2_GPIOInit();
    USART2_Init();
    USART_PeripheralControl(USART2, ENABLE);

    char *boot_msg = "MCU Booting... Initializing I2C Infrastructure.\r\n";
    USART_SendData(&usart2_handle, (uint8_t*)boot_msg, strlen(boot_msg));

    I2C1_GPIOInit();
    GPIOB->AFR[1] &= ~( (0xFU << 0) | (0xFU << 4) );
    GPIOB->AFR[1] |=  ( (0x4U << 0) | (0x4U << 4) );
    I2C1_Init();
    I2C_PeripheralControl(I2C1, ENABLE);
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

    // Display Setup
    LCD_Init(&i2c1_handle);
    LCD_Clear(&i2c1_handle);
    LCD_SetCursor(&i2c1_handle, 0, 0);
    LCD_SendString(&i2c1_handle, "LM75 TEMP MONITOR");

    while(1)
    {
        // 1. Fetch raw 16-bit data safely
        LM75_ReadTempRaw(&raw_temp);

        // 2. Process data: LM75 uses the upper 11 (or 9) bits of a 16-bit word.
        // Shifting right by 8 gives the integer part.
        int32_t integer_part = (int32_t)(raw_temp >> 8);

        // The remaining lower bits represent steps of 0.5, 0.25, 0.125, or 0.0625°C.
        // We multiply the fractional byte fraction by 100 to get a 2-digit integer for %02ld printing.
        uint32_t fractional_part = ((uint32_t)(raw_temp & 0x00FF) >> 5) * 12.5;

        /* --- 3. Transmit over USART2 --- */
        // Updated format tag from "[LM75 UPDATE]" to "[UPDATE]" to match your PuTTY screen
        sprintf(log_buffer, "[UPDATE]: Temp = %ld.%02ld C\r\n", integer_part, fractional_part);
        USART_SendData(&usart2_handle, (uint8_t*)log_buffer, strlen(log_buffer));

        /* --- 4. Update LCD Layout --- */
        sprintf(lcd_buffer, "Temp: %ld.%02ld C   ", integer_part, fractional_part);
        LCD_SetCursor(&i2c1_handle, 1, 0);
        LCD_SendString(&i2c1_handle, lcd_buffer);

        delay_ms(1000);
    }

    return 0;
}
