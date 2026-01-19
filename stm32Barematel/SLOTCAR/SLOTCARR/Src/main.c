#include <stdio.h>
#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_rcc_driver.h"
#include "lcd.h"

// -------------------- Configuration --------------------
#define TRIG1_PIN       GPIO_PIN_NO_6  // PA6
#define ECHO1_PIN       GPIO_PIN_NO_7  // PA7
#define ULTRASONIC_PORT GPIOA

#define SERVO_PIN       GPIO_PIN_NO_10 // PB10
#define SERVO_PORT      GPIOB

// -------------------- Global Variables --------------------
int Slot = 4;
int flag1 = 0;
const int distanceThreshold = 10; // cm

// -------------------- Function Prototypes --------------------
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
long getDistance(GPIO_RegDef_t *pGPIOx, uint8_t trigPin, uint8_t echoPin);
void servoMove(uint8_t angle);

int main(void)
{
    // 1. Enable Peripheral Clocks
    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    // 2. Initialize LCD
    lcd_init();
    lcd_set_cursor(0, 0);
    printf("stn32 larking");
    lcd_print("  STM32 PARKING ");
    lcd_set_cursor(1, 0);
    lcd_print("    SYSTEM    ");
    delay_ms(2000);
    lcd_clear();

    // 3. Initialize Ultrasonic Trigger Pin (Output)
    GPIO_Handle_t ultrasonic;
    ultrasonic.pGPIOx = ULTRASONIC_PORT;
    ultrasonic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    ultrasonic.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    ultrasonic.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    ultrasonic.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    ultrasonic.GPIO_PinConfig.GPIO_PinNumber = TRIG1_PIN;
    GPIO_Init(&ultrasonic);

    // 4. Initialize Ultrasonic Echo Pin (Input)
    ultrasonic.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    ultrasonic.GPIO_PinConfig.GPIO_PinNumber = ECHO1_PIN;
    GPIO_Init(&ultrasonic);

    // 5. Initialize Servo Pin
    GPIO_Handle_t servo;
    servo.pGPIOx = SERVO_PORT;
    servo.GPIO_PinConfig.GPIO_PinNumber = SERVO_PIN;
    servo.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    servo.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    servo.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    servo.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&servo);

    // Initial State
    servoMove(100); // Gate Closed

    while(1)
    {
        long distance1 = getDistance(ULTRASONIC_PORT, TRIG1_PIN, ECHO1_PIN);

        // --- Entry Logic ---
        if(distance1 < distanceThreshold && flag1 == 0)
        {
            if(Slot > 0)
            {
                flag1 = 1;
                servoMove(0); // Open
                Slot--;
            }
            else
            {
                lcd_clear();
                lcd_print("   SORRY :(   ");
                lcd_set_cursor(1, 0);
                lcd_print("  PARKING FULL ");
                delay_ms(2000);
            }
        }

        // --- Gate Reset Logic ---
        if(flag1 == 1)
        {
            delay_ms(3000);
            servoMove(100); // Close
            flag1 = 0;
        }

        // --- Update LCD ---
        lcd_set_cursor(0, 0);
        lcd_print("    WELCOME!    ");
        lcd_set_cursor(1, 0);
        lcd_print("Slots Left: ");
        char buf[10];
        printf(buf, "%d ", Slot); // Extra space clears old digits
        lcd_print(buf);

        delay_ms(200);
    }
}

// -------------------- Helper Functions --------------------

long getDistance(GPIO_RegDef_t *pGPIOx, uint8_t trigPin, uint8_t echoPin)
{
    // Start Trigger
    GPIO_WriteToOutputPin(pGPIOx, trigPin, RESET);
    delay_us(2);
    GPIO_WriteToOutputPin(pGPIOx, trigPin, SET);
    delay_us(10);
    GPIO_WriteToOutputPin(pGPIOx, trigPin, RESET);

    // Wait for Echo to go HIGH
    uint32_t timeout = 1000000;
    while(GPIO_ReadFromInputPin(pGPIOx, echoPin) == RESET && timeout--);

    // Measure High pulse width
    uint32_t count = 0;
    while(GPIO_ReadFromInputPin(pGPIOx, echoPin) == SET)
    {
        count++;
        delay_us(1);
        if(count > 25000) break; // Max limit
    }

    // count is roughly in microseconds if delay_us is calibrated
    return (count * 0.034 / 2);
}

void servoMove(uint8_t angle)
{
    // Pulse width in us: 0 deg ~ 500us, 180 deg ~ 2500us
    uint32_t duty = 500 + ((angle * 2000) / 180);
    for(int i = 0; i < 25; i++) // Send pulses for ~0.5 seconds
    {
        GPIO_WriteToOutputPin(SERVO_PORT, SERVO_PIN, SET);
        delay_us(duty);
        GPIO_WriteToOutputPin(SERVO_PORT, SERVO_PIN, RESET);
        delay_us(20000 - duty);
    }
}

void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms; i++) delay_us(1000);
}

void delay_us(uint32_t us)
{
    // For 16MHz (Default HSI), approx 3-4 loops = 1us.
    // If you use PLL (180MHz), this must be increased to ~45.
    for(uint32_t i = 0; i < us; i++)
    {
        for(uint32_t j = 0; j < 4; j++);
    }
}
