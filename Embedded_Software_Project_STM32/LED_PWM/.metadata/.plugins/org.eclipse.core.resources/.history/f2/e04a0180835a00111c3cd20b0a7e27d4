#include "stm32f446xx_usart_driver.h"
#include "stm32f446xx_rcc_driver.h"

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
    uint32_t PCLKx, usartdiv, M_part, F_part, tempreg = 0;

    PCLKx = (pUSARTx == USART1 || pUSARTx == USART6) ? RCC_GetPCLK2Value() : RCC_GetPCLK1Value();

    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8)) {
        usartdiv = ((25 * PCLKx) / (2 * BaudRate));
    } else {
        usartdiv = ((25 * PCLKx) / (4 * BaudRate));
    }

    M_part = usartdiv / 100;
    tempreg |= M_part << 4;
    F_part = (usartdiv - (M_part * 100));

    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8)) {
        F_part = (((F_part * 8) + 50) / 100) & 0x07;
    } else {
        F_part = (((F_part * 16) + 50) / 100) & 0x0F;
    }

    tempreg |= F_part;
    pUSARTx->BRR = tempreg;
}

/*
 * @fn      - USART_Init
 * @brief   - Initializes the USART peripheral configuration registers
 * @param   - Handle structure pointer for the target USART configuration
 * @return  - none
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{
    uint32_t tempreg = 0;

    // 1. Enable the Peripheral Clock for the chosen USARTx instance
    USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

    /*********************************** CR1 Configuration **********************************/

    // Configure the hardware mode options (TX, RX, or TXRX)
    if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        tempreg |= (1 << USART_CR1_TE); // Enable Transmitter
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
    {
        tempreg |= (1 << USART_CR1_RE); // Enable Receiver
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        // Enable BOTH Transmitter and Receiver bits!
        tempreg |= (1 << USART_CR1_TE) | (1 << USART_CR1_RE);
    }

    // Configure Word Length (M bit)
    tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;

    // Configure Parity Control
    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        tempreg |= (1 << USART_CR1_PCE); // Enable Parity Control
        tempreg &= ~(1 << USART_CR1_PS); // Clear PS bit for Even Parity
    }
    else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        tempreg |= (1 << USART_CR1_PCE); // Enable Parity Control
        tempreg |= (1 << USART_CR1_PS);  // Set PS bit for Odd Parity
    }
    // If USART_PARITY_DISABLE, PCE and PS bits remain 0

    // Save configuration parameters down to CR1 register
    pUSARTHandle->pUSARTx->CR1 = tempreg;

    /*********************************** CR2 Configuration **********************************/

    tempreg = 0;

    // Configure Number of Stop Bits
    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

    // Save configuration parameters down to CR2 register
    pUSARTHandle->pUSARTx->CR2 = tempreg;

    /*********************************** CR3 Configuration **********************************/

    tempreg = 0;

    // Configure Hardware Flow Control
    if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        tempreg |= (1 << USART_CR3_CTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        tempreg |= (1 << USART_CR3_RTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        tempreg |= (1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE);
    }

    // Save configuration parameters down to CR3 register
    pUSARTHandle->pUSARTx->CR3 = tempreg;

    /*********************************** BRR Configuration **********************************/

    // Set Up Baud Rate configuration settings using the mathematical clock dividers
    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
}
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t Cmd)
{
    if(Cmd == ENABLE) { pUSARTx->CR1 |= (1 << 13); }
    else              { pUSARTx->CR1 &= ~(1 << 13); }
}

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE) {
        if      (pUSARTx == USART2) { USART2_PCLK_EN(); }
    }
}

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
    return (pUSARTx->SR & StatusFlagName) ? SET : RESET;
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    for(uint32_t i = 0 ; i < Len; i++)
    {
        while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE));
        pUSARTHandle->pUSARTx->DR = (*pTxBuffer & 0xFF);
        pTxBuffer++;
    }
    while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC));
}
