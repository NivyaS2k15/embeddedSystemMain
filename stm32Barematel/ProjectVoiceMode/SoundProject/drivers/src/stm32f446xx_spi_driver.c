/*
 * stm32f446xx_spi_driver.c
 * Corrected & Stable Version
 */

#include "stm32f446xx_spi_driver.h"

/* ---------- Peripheral Clock ---------- */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(pSPIx == SPI1) SPI1_PCLK_EN();
        else if(pSPIx == SPI2) SPI2_PCLK_EN();
        else if(pSPIx == SPI3) SPI3_PCLK_EN();
        else if(pSPIx == SPI4) SPI4_PCLK_EN();
    }
    else
    {
        if(pSPIx == SPI1) SPI1_PCLK_DI();
        else if(pSPIx == SPI2) SPI2_PCLK_DI();
        else if(pSPIx == SPI3) SPI3_PCLK_DI();
        else if(pSPIx == SPI4) SPI4_PCLK_DI();
    }
}

/* ---------- Init ---------- */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

    uint32_t tempreg = 0;

    tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
        tempreg &= ~(1 << SPI_CR1_BIDIMODE);
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
        tempreg |= (1 << SPI_CR1_BIDIMODE);
    else
    {
        tempreg &= ~(1 << SPI_CR1_BIDIMODE);
        tempreg |= (1 << SPI_CR1_RXONLY);
    }

    tempreg |= pSPIHandle->SPIConfig.SPI_DFF  << SPI_CR1_DFF;
    tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
    tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
    tempreg |= pSPIHandle->SPIConfig.SPI_SSM  << SPI_CR1_SSM;

    pSPIHandle->pSPIx->CR1 = tempreg;

    /* Enable error interrupt (IMPORTANT) */
    pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_ERRIE);
}

/* ---------- Enable / Disable ---------- */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    else
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
}

/* ---------- Flag ---------- */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
    return (pSPIx->SR & FlagName) ? FLAG_SET : FLAG_RESET;
}

/* ---------- Blocking Send ---------- */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

        if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            uint16_t *temp = (uint16_t*)pTxBuffer;
            pSPIx->DR = *temp;
            pTxBuffer += 2;
            Len -= 2;
        }
        else
        {
            pSPIx->DR = *pTxBuffer;
            pTxBuffer++;
            Len--;
        }
    }
}

/* ---------- Blocking Receive (SAFE) ---------- */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    uint32_t timeout;

    while(Len > 0)
    {
        timeout = 200000;
        while((SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET) && timeout--);

        if(timeout == 0) return;   // prevents debugger lock

        if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
        {
            uint16_t *temp = (uint16_t*)pRxBuffer;
            *temp = pSPIx->DR;
            pRxBuffer += 2;
            Len -= 2;
        }
        else
        {
            *pRxBuffer = pSPIx->DR;
            pRxBuffer++;
            Len--;
        }
    }
}

/* ---------- Clear OVR ---------- */
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
    uint8_t temp;
    temp = pSPIx->DR;
    temp = pSPIx->SR;
    (void)temp;
}

/* ---------- Close ---------- */
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
    pSPIHandle->RxState = SPI_READY;
}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
    pSPIHandle->TxState = SPI_READY;
}

/* ---------- Weak Callback ---------- */
__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{
    // User override
}
