#include "stm32f446xx_usart_driver.h"

/*********************************************************************
 * @fn      		  - USART_PeriClockControl
 * @brief             - Enable or Disable USART peripheral clock
 *********************************************************************/
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pUSARTx == USART1) USART1_PCLK_EN();
		else if(pUSARTx == USART2) USART2_PCLK_EN();
		else if(pUSARTx == USART3) USART3_PCLK_EN();
		else if(pUSARTx == UART4) UART4_PCLK_EN();
		else if(pUSARTx == UART5) UART5_PCLK_EN();
		else if(pUSARTx == USART6) USART6_PCLK_EN();
	}
	else
	{
		if(pUSARTx == USART1) USART1_PCLK_DI();
		else if(pUSARTx == USART2) USART2_PCLK_DI();
		else if(pUSARTx == USART3) USART3_PCLK_DI();
		else if(pUSARTx == UART4) UART4_PCLK_DI();
		else if(pUSARTx == UART5) UART5_PCLK_DI();
		else if(pUSARTx == USART6) USART6_PCLK_DI();
	}
}


/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *********************************************************************/
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx, usartdiv, M_part, F_part;
	uint32_t tempreg = 0;

	if(pUSARTx == USART1 || pUSARTx == USART6)
	{
		PCLKx = RCC_GetPCLK2Value();
	}
	else
	{
		PCLKx = RCC_GetPCLK1Value();
	}

	usartdiv = (25 * PCLKx) / (4 * BaudRate);

	M_part = usartdiv / 100;
	tempreg |= (M_part << 4);

	F_part = usartdiv - (M_part * 100);

	F_part = (((F_part * 16) + 50) / 100) & ((uint8_t)0x0F);

	tempreg |= F_part;

	pUSARTx->BRR = tempreg;
}


/*********************************************************************
 * @fn      		  - USART_Init
 *********************************************************************/
void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg = 0;

	// Enable peripheral clock
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	/*************** CR1 CONFIG ***************/

	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		tempreg |= (1 << USART_CR1_RE);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		tempreg |= (1 << USART_CR1_TE);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		tempreg |= (1 << USART_CR1_TE);
		tempreg |= (1 << USART_CR1_RE);
	}

	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;
	tempreg |= pUSARTHandle->USART_Config.USART_ParityControl << USART_CR1_PCE;

	pUSARTHandle->pUSARTx->CR1 = tempreg;

	/*************** CR2 CONFIG ***************/
	tempreg = 0;
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;
	pUSARTHandle->pUSARTx->CR2 = tempreg;

	/*************** CR3 CONFIG ***************/
	tempreg = 0;

	tempreg |= pUSARTHandle->USART_Config.USART_HWFlowControl << USART_CR3_CTSE;

	pUSARTHandle->pUSARTx->CR3 = tempreg;

	// Configure baud rate
	USART_SetBaudRate(pUSARTHandle->pUSARTx,
					  pUSARTHandle->USART_Config.USART_Baud);

	// Enable USART peripheral
	USART_PeripheralControl(pUSARTHandle->pUSARTx, ENABLE);
}


/*********************************************************************
 * @fn      		  - USART_DeInit
 *********************************************************************/
void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	if(pUSARTx == USART1) USART1_REG_RESET();
	else if(pUSARTx == USART2) USART2_REG_RESET();
	else if(pUSARTx == USART3) USART3_REG_RESET();
	else if(pUSARTx == UART4) UART4_REG_RESET();
	else if(pUSARTx == UART5) UART5_REG_RESET();
	else if(pUSARTx == USART6) USART6_REG_RESET();
}


/*********************************************************************
 * @fn      		  - USART_PeripheralControl
 *********************************************************************/
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}
	else
	{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}


/*********************************************************************
 * @fn      		  - USART_SendData
 *********************************************************************/
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;

	for(uint32_t i = 0; i < Len; i++)
	{
		while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TXE));

		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			pdata = (uint16_t*) pTxBuffer;

			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				pTxBuffer += 2;
			}
			else
			{
				pTxBuffer++;
			}
		}
		else
		{
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
			pTxBuffer++;
		}
	}

	while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC));
}


/*********************************************************************
 * @fn      		  - USART_GetFlagStatus
 *********************************************************************/
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t FlagName)
{
	if(pUSARTx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


/*********************************************************************
 * @fn      		  - USART_ClearFlag
 *********************************************************************/
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
	pUSARTx->SR &= ~(StatusFlagName);
}


/*********************************************************************
 * @fn      		  - USART_IRQInterruptConfig
 *********************************************************************/
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ISER2 |= (1 << (IRQNumber % 32));
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			*NVIC_ICER2 |= (1 << (IRQNumber % 32));
		}
	}
}


/*********************************************************************
 * @fn      		  - USART_IRQHandling
 *********************************************************************/
void USART_IRQHandling(USART_Handle_t *pHandle)
{
	uint32_t temp1, temp2;

	/************** TXE **************/
	temp1 = pHandle->pUSARTx->SR & (1 << USART_SR_TXE);
	temp2 = pHandle->pUSARTx->CR1 & (1 << USART_CR1_TXEIE);

	if(temp1 && temp2)
	{
		USART_ApplicationEventCallback(pHandle, USART_EVENT_TX_CMPLT);
	}

	/************** RXNE **************/
	temp1 = pHandle->pUSARTx->SR & (1 << USART_SR_RXNE);
	temp2 = pHandle->pUSARTx->CR1 & (1 << USART_CR1_RXNEIE);

	if(temp1 && temp2)
	{
		USART_ApplicationEventCallback(pHandle, USART_EVENT_RX_CMPLT);
	}

	/************** IDLE **************/
	temp1 = pHandle->pUSARTx->SR & (1 << USART_SR_IDLE);
	temp2 = pHandle->pUSARTx->CR1 & (1 << USART_CR1_IDLEIE);

	if(temp1 && temp2)
	{
		temp1 = pHandle->pUSARTx->SR;
		temp1 = pHandle->pUSARTx->DR;

		USART_ApplicationEventCallback(pHandle, USART_EVENT_IDLE);
	}
}


/*********************************************************************
 * @fn      		  - Weak callback
 *********************************************************************/
__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv)
{

}
