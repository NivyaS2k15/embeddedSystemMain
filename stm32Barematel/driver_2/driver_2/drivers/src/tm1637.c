/*
 * tm1637.c
 *
 *  Created on: Feb 6, 2026
 *      Author: NIVYA
 */


#include "tm1637.h"

/* GPIO handles */
static GPIO_Handle_t TM_CLK;
static GPIO_Handle_t TM_DIO;

/* 7-segment map */
static const uint8_t segMap[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

/* Local delay */
static void tm_delay(void)
{
    for (volatile uint32_t i = 0; i < 150; i++);
}

/* Pin control macros using YOUR driver */
#define CLK_HIGH()  GPIO_WriteToOutputPin(TM1637_CLK_PORT, TM1637_CLK_PIN, GPIO_PIN_SET)
#define CLK_LOW()   GPIO_WriteToOutputPin(TM1637_CLK_PORT, TM1637_CLK_PIN, GPIO_PIN_RESET)

#define DIO_HIGH()  GPIO_WriteToOutputPin(TM1637_DIO_PORT, TM1637_DIO_PIN, GPIO_PIN_SET)
#define DIO_LOW()   GPIO_WriteToOutputPin(TM1637_DIO_PORT, TM1637_DIO_PIN, GPIO_PIN_RESET)

/* TM1637 protocol */
static void TM1637_Start(void)
{
    DIO_HIGH();
    CLK_HIGH();
    tm_delay();
    DIO_LOW();
}

static void TM1637_Stop(void)
{
    CLK_LOW();
    tm_delay();
    DIO_LOW();
    tm_delay();
    CLK_HIGH();
    tm_delay();
    DIO_HIGH();
}

static void TM1637_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        CLK_LOW();

        if (data & 0x01)
            DIO_HIGH();
        else
            DIO_LOW();

        data >>= 1;
        tm_delay();
        CLK_HIGH();
        tm_delay();
    }

    // ACK (ignored)
    CLK_LOW();
    tm_delay();
    CLK_HIGH();
    tm_delay();
}

/* Public functions */

void TM1637_Init(void)
{
    /* CLK pin */
    TM_CLK.pGPIOx = TM1637_CLK_PORT;
    TM_CLK.GPIO_PinConfig.GPIO_PinNumber = TM1637_CLK_PIN;
    TM_CLK.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    TM_CLK.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    TM_CLK.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    TM_CLK.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&TM_CLK);

    /* DIO pin */
    TM_DIO.pGPIOx = TM1637_DIO_PORT;
    TM_DIO.GPIO_PinConfig.GPIO_PinNumber = TM1637_DIO_PIN;
    TM_DIO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    TM_DIO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    TM_DIO.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    TM_DIO.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&TM_DIO);
}

void TM1637_DisplayTime(uint8_t hour, uint8_t min)
{
    // Command 1: auto increment
    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_Stop();

    // Command 2: address
    TM1637_Start();
    TM1637_WriteByte(0xC0);

    TM1637_WriteByte(segMap[hour / 10]);
    TM1637_WriteByte(segMap[hour % 10] | 0x80); // colon ON
    TM1637_WriteByte(segMap[min / 10]);
    TM1637_WriteByte(segMap[min % 10]);

    TM1637_Stop();

    // Command 3: display ON, brightness max
    TM1637_Start();
    TM1637_WriteByte(0x8F);
    TM1637_Stop();
}
