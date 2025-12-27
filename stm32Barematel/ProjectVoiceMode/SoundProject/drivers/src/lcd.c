/*
 * lcd.c
 *
 *  Created on: Dec 26, 2025
 *      Author: NIVYA
 */

#include "lcd.h"

// ---------------- Delay functions ----------------
static void delay_us(uint32_t us)
{
    for (volatile uint32_t i = 0; i < us * 8; i++);
}

static void delay_ms(uint32_t ms)
{
    while (ms--)
        delay_us(1000);
}

// ---------------- Enable Pulse ----------------
static void lcd_enable_pulse(void)
{
    GPIO_WriteToOutputPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    delay_us(5);
    GPIO_WriteToOutputPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
    delay_us(50);
}

// ---------------- Send Nibble ----------------
static void lcd_send_nibble(uint8_t nib)
{
    GPIO_WriteToOutputPin(LCD_D7_PORT, LCD_D7_PIN, (nib & 0x08) ? 1 : 0);
    GPIO_WriteToOutputPin(LCD_D6_PORT, LCD_D6_PIN, (nib & 0x04) ? 1 : 0);
    GPIO_WriteToOutputPin(LCD_D5_PORT, LCD_D5_PIN, (nib & 0x02) ? 1 : 0);
    GPIO_WriteToOutputPin(LCD_D4_PORT, LCD_D4_PIN, (nib & 0x01) ? 1 : 0);

    lcd_enable_pulse();
}

// ---------------- Send Byte ----------------
static void lcd_send_byte(uint8_t value, uint8_t rs)
{
    GPIO_WriteToOutputPin(LCD_RS_PORT, LCD_RS_PIN, rs);

    lcd_send_nibble(value >> 4);     // upper nibble
    lcd_send_nibble(value & 0x0F);   // lower nibble
}

// ---------------- LCD Commands ----------------
void lcd_cmd(uint8_t cmd)
{
    lcd_send_byte(cmd, 0);

    if (cmd == 0x01 || cmd == 0x02)
        delay_ms(2);
}

// ---------------- LCD Data ----------------
void lcd_data(uint8_t data)
{
    lcd_send_byte(data, 1);
}

// ---------------- Cursor ----------------
void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row ? 0x40 : 0x00) + col;
    lcd_cmd(0x80 | addr);
}

// ---------------- Clear ----------------
void lcd_clear(void)
{
    lcd_cmd(0x01);
}

// ---------------- Print String ----------------
void lcd_print(const char *str)
{
    while (*str)
        lcd_data(*str++);
}

// ---------------- LCD Init ----------------
void lcd_init(void)
{
    // Enable clocks
    GPIO_PeriClockControl(LCD_RS_PORT, ENABLE);
    GPIO_PeriClockControl(LCD_EN_PORT, ENABLE);
    GPIO_PeriClockControl(LCD_D4_PORT, ENABLE);
    GPIO_PeriClockControl(LCD_D5_PORT, ENABLE);
    GPIO_PeriClockControl(LCD_D6_PORT, ENABLE);
    GPIO_PeriClockControl(LCD_D7_PORT, ENABLE);

    GPIO_Handle_t lcdPin = {0};
    lcdPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    lcdPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    lcdPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    lcdPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    // RS
    lcdPin.pGPIOx = LCD_RS_PORT;
    lcdPin.GPIO_PinConfig.GPIO_PinNumber = LCD_RS_PIN;
    GPIO_Init(&lcdPin);

    // EN
    lcdPin.pGPIOx = LCD_EN_PORT;
    lcdPin.GPIO_PinConfig.GPIO_PinNumber = LCD_EN_PIN;
    GPIO_Init(&lcdPin);

    // D4
    lcdPin.pGPIOx = LCD_D4_PORT;
    lcdPin.GPIO_PinConfig.GPIO_PinNumber = LCD_D4_PIN;
    GPIO_Init(&lcdPin);

    // D5
    lcdPin.pGPIOx = LCD_D5_PORT;
    lcdPin.GPIO_PinConfig.GPIO_PinNumber = LCD_D5_PIN;
    GPIO_Init(&lcdPin);

    // D6
    lcdPin.pGPIOx = LCD_D6_PORT;
    lcdPin.GPIO_PinConfig.GPIO_PinNumber = LCD_D6_PIN;
    GPIO_Init(&lcdPin);

    // D7
    lcdPin.pGPIOx = LCD_D7_PORT;
    lcdPin.GPIO_PinConfig.GPIO_PinNumber = LCD_D7_PIN;
    GPIO_Init(&lcdPin);

    delay_ms(20);

    // LCD init sequence
    lcd_send_nibble(0x03);
    delay_ms(5);
    lcd_send_nibble(0x03);
    delay_us(150);
    lcd_send_nibble(0x03);
    delay_us(150);

    lcd_send_nibble(0x02); // 4-bit mode

    lcd_cmd(0x28); // 4-bit, 2-line, 5x8 font
    lcd_cmd(0x08); // display off
    lcd_cmd(0x01); // clear
    lcd_cmd(0x06); // entry mode
    lcd_cmd(0x0C); // display ON, cursor OFF
}

// ---------------- Print Integer ----------------
void lcd_print_uint16(uint16_t value)
{
    uint16_t divisors[] = {10000, 1000, 100, 10, 1};
    uint8_t started = 0;

    for (uint8_t i = 0; i < 5; i++)
    {
        uint8_t digit = value / divisors[i];
        if (digit || started || i == 4)
        {
            lcd_data('0' + digit);
            started = 1;
        }
        value %= divisors[i];
    }
}
