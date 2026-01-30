#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

/* Initialize TWI/I2C */
void I2C_Init(void);

/* Send START condition */
void I2C_Start(void);

/* Send STOP condition */
void I2C_Stop(void);

/* Write byte to I2C bus */
void I2C_Write(uint8_t data);

/* Read byte from I2C bus with ACK */
uint8_t I2C_Read_ACK(void);

/* Read byte from I2C bus with NACK */
uint8_t I2C_Read_NACK(void);

#endif /* I2C_H_ */