/*
 * stm32f446xx_spi_driver.c
 * SPI implementation featuring direct address clock mappings to bypass macro errors
 */

#include "stm32f446xx_spi_driver.h"

// Direct bare-metal definitions to bypass any header file irregularities
#define RCC_BASE_ADDR      0x40023800UL
#define RCC_APB2ENR_PTR    ((__vo uint32_t*)(RCC_BASE_ADDR + 0x44))

void SPI1_Init(void)
{
    // 1. Force enable SPI1 Clock using a direct pointer to APB2ENR (Bit 12)
    *RCC_APB2ENR_PTR |= (1 << 12);

    // 2. Clear out the pipe with a multi-cycle dummy read loop to guarantee stability
    for(__vo uint32_t i = 0; i < 500; i++);

    uint32_t tempreg = 0;

    // 3. Configure control register settings
    tempreg |= (1 << 2);   // MSTR = 1 : Configure STM32 as SPI Master
    tempreg |= (0 << 11);  // DFF = 0  : 8-bit Data Frame Format
    tempreg |= (0 << 1);   // CPOL = 0 : Clock idles LOW
    tempreg |= (0 << 0);   // CPHA = 0 : Sampling occurs on first clock edge
    tempreg |= (1 << 9);   // SSM = 1  : Enable Software Slave Management
    tempreg |= (1 << 8);   // SSI = 1  : Drive Internal Slave Select bit HIGH

    // Set Baud Rate to /64 (0x5 << 3) to keep the signals clean on a breadboard
    tempreg |= (0x5 << 3);

    // Safely write to the register
    SPI1->CR1 = tempreg;
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |=  (1 << 6); // SPE = 1
    }
    else
    {
        pSPIx->CR1 &= ~(1 << 6);
    }
}

uint8_t SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    uint32_t timeout = 50000;
    while(Len > 0)
    {
        while( ! (pSPIx->SR & (1 << 1)) ) // Wait for TXE flag
        {
            if(--timeout == 0) return 0;
        }
        pSPIx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }
    return 1;
}

uint8_t SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    uint32_t timeout = 50000;
    while(Len > 0)
    {
        while( ! (pSPIx->SR & (1 << 0)) ) // Wait for RXNE flag
        {
            if(--timeout == 0) return 0;
        }
        *pRxBuffer = pSPIx->DR;
        pRxBuffer++;
        Len--;
    }
    return 1;
}
