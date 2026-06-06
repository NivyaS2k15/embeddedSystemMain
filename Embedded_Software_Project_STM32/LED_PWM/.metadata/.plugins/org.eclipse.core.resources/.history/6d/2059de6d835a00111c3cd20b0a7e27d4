#ifndef STM32F446XX_I2C_DRIVER_H
#define STM32F446XX_I2C_DRIVER_H

#include "stm32f446xx.h"

typedef struct {
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_AckControl;
} I2C_Config_t;

typedef struct {
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2C_Config;
} I2C_Handle_t;

#define I2C_SCL_SPEED_SM       100000
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0

#define I2C_ENABLE_SR          1
#define I2C_DISABLE_SR         0

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr, uint8_t Sr);

#endif
