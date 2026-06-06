#ifndef INC_STM32F446XX_USART_DRIVER_H_
#define INC_STM32F446XX_USART_DRIVER_H_

#include "stm32f446xx.h"

typedef struct
{
    uint8_t USART_Mode;
    uint32_t USART_Baud;
    uint8_t USART_NoOfStopBits;
    uint8_t USART_WordLength;
    uint8_t USART_ParityControl;
    uint8_t USART_HWFlowControl;
} USART_Config_t;

typedef struct
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t   USART_Config;
} USART_Handle_t;
/*
 * @USART_ParityControl
 * Possible options for USART_ParityControl
 */
#define USART_PARITY_DISABLE     0
#define USART_PARITY_EN_EVEN     1    /* <-- ADD THIS LINE */
#define USART_PARITY_EN_ODD      2    /* <-- ADD THIS LINE */

/*
 * @USART_HWFlowControl
 * Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    0
#define USART_HW_FLOW_CTRL_CTS     1  /* <-- ADD THIS LINE */
#define USART_HW_FLOW_CTRL_RTS     2  /* <-- ADD THIS LINE */
#define USART_HW_FLOW_CTRL_CTS_RTS 3  /* <-- ADD THIS LINE */

#define USART_MODE_ONLY_TX          0
#define USART_MODE_ONLY_RX     1
#define USART_MODE_TXRX        2  /* <-- ADD THIS LINE */
#define USART_STD_BAUD_115200       115200
#define USART_PARITY_DISABLE        0
#define USART_WORDLEN_8BITS         0
#define USART_STOPBITS_1            0
#define USART_HW_FLOW_CTRL_NONE     0

#define USART_FLAG_TXE      (1 << 7)
#define USART_FLAG_RXNE        (1 << 5)
#define USART_FLAG_TC       (1 << 6)

void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);

#endif /* INC_STM32F446XX_USART_DRIVER_H_ */
