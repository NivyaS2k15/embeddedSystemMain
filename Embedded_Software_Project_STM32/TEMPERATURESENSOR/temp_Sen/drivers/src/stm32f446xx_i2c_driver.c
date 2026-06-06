#include "stm32f446xx_i2c_driver.h"
#include "stm32f446xx_rcc_driver.h"

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE) { RCC->APB1ENR |= (1 << 21); }
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;

    // 1. Calculate and set FREQ fields based on the actual APB1 bus speed
    uint32_t pclk1 = RCC_GetPCLK1Value();
    tempreg = pclk1 / 1000000;
    pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

    // 2. Compute Clock Control Register Value (CCR)
    tempreg = 0;
    uint32_t ccr_value = pclk1 / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
    tempreg |= (ccr_value & 0xFFF);
    pI2CHandle->pI2Cx->CCR = tempreg;

    // 3. Set Rise Time Limit Parameters (TRISE Register)
    uint32_t trise = (pclk1 / 1000000) + 1;
    pI2CHandle->pI2Cx->TRISE = (trise & 0x3F);
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)  { pI2Cx->CR1 |=  (1 << 0); }
    else                 { pI2Cx->CR1 &= ~(1 << 0); }
}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)  { pI2Cx->CR1 |=  (1 << 10); }
    else                 { pI2Cx->CR1 &= ~(1 << 10); }
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    // A. Issue Start Condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
    while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_SB)) );

    // B. Push Shifted Address + Write Bit (0)
    I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);
    while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR)) );
    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    // C. Stream Out Data Packet Payload Array
    for(uint32_t i = 0; i < Len; i++) {
        while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TXE)) );
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
    }

    while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TXE)) );
    while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_BTF)) );

    // D. Terminate with Stop Condition unless Repeated Start is active
    if(Sr == I2C_DISABLE_SR) { I2C_GenerateStopCondition(pI2CHandle->pI2Cx); }
}

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
    while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_SB)) );

    // Push Shifted Address + Read Bit (1)
    I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, SlaveAddr);
    while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR)) );

    if(Len == 1) {
        I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
        while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_RXNE)) );
        if(Sr == I2C_DISABLE_SR) { I2C_GenerateStopCondition(pI2CHandle->pI2Cx); }
        *pRxBuffer = pI2CHandle->pI2Cx->DR;
    }
    else {
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
        for(uint32_t i = Len; i > 0; i--) {
            while( ! (pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_RXNE)) );
            if(i == 2) {
                I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
                if(Sr == I2C_DISABLE_SR) { I2C_GenerateStopCondition(pI2CHandle->pI2Cx); }
            }
            *pRxBuffer = pI2CHandle->pI2Cx->DR;
            pRxBuffer++;
        }
    }
    if(pI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_ENABLE) {
        I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
    }
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)   { pI2Cx->CR1 |= (1 << 8);  }
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)    { pI2Cx->CR1 |= (1 << 9);  }

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx,
                                         uint8_t SlaveAddr)
{
    uint32_t timeout = 1000000;

    pI2Cx->DR = (SlaveAddr << 1);

    while(!(pI2Cx->SR1 & (1 << I2C_SR1_ADDR)))
    {
        if(pI2Cx->SR1 & (1 << I2C_SR1_AF))
        {
            pI2Cx->SR1 &= ~(1 << I2C_SR1_AF);

            USART2->DR = 'F';   // Failure marker

            return;
        }

        if(--timeout == 0)
        {
            USART2->DR = 'T';   // Timeout marker

            return;
        }
    }
}


static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    uint32_t timeout = 1000000;

    pI2Cx->DR = (SlaveAddr << 1) | 0x01;

    while(!(pI2Cx->SR1 & (1 << I2C_SR1_ADDR)))
    {
        if(pI2Cx->SR1 & (1 << I2C_SR1_AF))
        {
            pI2Cx->SR1 &= ~(1 << I2C_SR1_AF);
            return;
        }

        if(--timeout == 0)
        {
            return;
        }
    }
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx) {
    uint32_t dummyRead = pI2Cx->SR1;
    dummyRead = pI2Cx->SR2;
    (void)dummyRead; // Suppress compiler warnings
}
