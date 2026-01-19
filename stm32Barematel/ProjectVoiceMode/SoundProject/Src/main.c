/*
 * main.c
 * STM32F446 SPI1 SLAVE
 */

#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_spi_driver.h"
#include <stdio.h>

SPI_Handle_t SPI1Handle;
uint8_t rxBuf[3];

/* ---------- GPIO Init ---------- */
void SPI1_GPIOInit(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    // SCK - PA5
    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GPIO_Init(&SPIPins);

    // MISO - PA6
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&SPIPins);

    // MOSI - PA7
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&SPIPins);

    // NSS - PA4
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
    GPIO_Init(&SPIPins);
}

/* ---------- SPI Init ---------- */
void SPI1_Init(void)
{
    SPI1Handle.pSPIx = SPI1;
    SPI1Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_SLAVE;
    SPI1Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI1Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI1Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI1Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI1Handle.SPIConfig.SPI_SSM  = SPI_SSM_DI;   // Hardware NSS

    SPI_Init(&SPI1Handle);
}

int main(void)
{
    SPI1_GPIOInit();
    SPI1_Init();

    SPI_PeripheralControl(SPI1, ENABLE);

    printf("STM32 SPI SLAVE READY\n");

    while(1)
    {
        // Wait until master selects slave (NSS LOW)
        while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_4));

        SPI_ReceiveData(SPI1, rxBuf, 3);

        printf("RX: %c %c %c\n", rxBuf[0], rxBuf[1], rxBuf[2]);
    }
}
