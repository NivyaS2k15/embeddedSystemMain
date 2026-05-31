/*
 * stm32f446xx_spi_driver.h
 * Bare-metal SPI peripheral driver layout configuration with Timeout Guards
 */

#ifndef STM32F446XX_SPI_DRIVER_H
#define STM32F446XX_SPI_DRIVER_H

#include "stm32f446xx.h"

#define SPI1_BASE             (APB2PERIPH_BASEADDR + 0x3000UL)
#define SPI1                  ((SPI_RegDef_t*)SPI1_BASE)

typedef struct {
    __vo uint32_t CR1;        // SPI control register 1
    __vo uint32_t CR2;        // SPI control register 2
    __vo uint32_t SR;         // SPI status register
    __vo uint32_t DR;         // SPI data register
    __vo uint32_t CRCPR;      // SPI CRC polynomial register
    __vo uint32_t RXCRCR;     // SPI RX CRC register
    __vo uint32_t TXCRCR;     // SPI TX CRC register
    __vo uint32_t I2SCFGR;    // SPI_I2S configuration register
    __vo uint32_t I2SPR;      // SPI_I2S prescaler register
} SPI_RegDef_t;

// Driver API Functions
void SPI1_Init(void);
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// SIGNATURES FIXED: Now correctly defined as returning uint8_t to match the .c source
uint8_t SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

#endif /* STM32F446XX_SPI_DRIVER_H */
