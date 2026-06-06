/*
 * stm32f446xx_spi_driver.c
 *
 * Created on: Jun 6, 2026
 * Author: NIVYA
 */

#include "stm32f446xx_spi_driver.h"

/*********************************************************************
 * @fn      - SPI_PeriClockControl
 * @brief   - This function enables or disables the peripheral clock for the given SPI port
 *********************************************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            // If your macro is spelled slightly differently, match that spelling here:
            RCC->APB2ENR |= (1 << 12); // Directly sets the SPI1EN bit in the RCC APB2 register
        }
    }
    else
    {
        if (pSPIx == SPI1)
        {
            RCC->APB2ENR &= ~(1 << 12); // Directly clears the SPI1EN bit
        }
    }
}
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    uint32_t tempreg = 0;

    // 1. Configure device mode (Master)
    tempreg |= (pSPIHandle->SPI_Config.SPI_DeviceMode << 2);

    // 2. Configure bus configuration (Full Duplex)
    if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX) {
        tempreg &= ~(1 << 15); // Clear BIDIMODE
    }

    // 3. Configure Clock Speed (Baud rate prescaler)
    tempreg |= (pSPIHandle->SPI_Config.SPI_SclkSpeed << 3);

    // 4. Configure Data Frame Format (DFF)
    tempreg |= (pSPIHandle->SPI_Config.SPI_DFF << 11);

    // 5. Configure CPOL & CPHA
    tempreg |= (pSPIHandle->SPI_Config.SPI_CPOL << 1);
    tempreg |= (pSPIHandle->SPI_Config.SPI_CPHA << 0);

    // 6. Configure Software Slave Management (SSM)
    tempreg |= (pSPIHandle->SPI_Config.SPI_SSM << 9);
    tempreg |= (1 << 8); // Set SSI bit high to avoid MODF fault in Master mode

    pSPIHandle->pSPIx->CR1 = tempreg;
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while (Len > 0) {
        // Wait until TXE (Transmit buffer empty) flag is SET
        while (!(pSPIx->SR & (1 << 1)));

        // Load data into Data Register
        pSPIx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }
}

uint8_t SPI_SendReceiveByte(SPI_RegDef_t *pSPIx, uint8_t txByte)
{
    // 1. Wait until TXE (Transmit buffer empty) flag is SET
    while (!(pSPIx->SR & (1 << 1)));

    // 2. Write data to be transmitted
    pSPIx->DR = txByte;

    // 3. Wait until RXNE (Receive buffer not empty) flag is SET
    while (!(pSPIx->SR & (1 << 0)));

    // 4. Return the received data shifted in from the slave
    return (uint8_t)pSPIx->DR;
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE) {
        pSPIx->CR1 |= (1 << 6); // Set SPE bit
    } else {
        pSPIx->CR1 &= ~(1 << 6); // Clear SPE bit
    }
}
