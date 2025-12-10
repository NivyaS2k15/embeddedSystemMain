/*
 * stm32f446xx.h
 *
 *  Created on: Nov 19, 2025
 *      Author: NIVYA
 */

#ifndef STM32F446XX_H_
#define STM32F446XX_H_
#include <stdint.h>

/*GPIO BASE ADDRESS address(Ahb1)*/
#define GPIOA_BASEADDR 0x40020000U
#define GPIOB_BASEADDR 0x40020400U
#define GPIOC_BASEADDR 0x40020800U
#define GPIOD_BASEADDR 0x40020C00U
#define GPIOE_BASEADDR 0x40021000U
#define GPIOF_BASEADDR 0x40021400U
#define GPIOG_BASEADDR 0x40021800U
#define GPIOH_BASEADDR 0x40021C00U

/*GPIO REGISTER STRUCTURE
 *
 */

typedef struct
{
    volatile uint32_t MODER;    // GPIO port mode register              (0x00)
    volatile uint32_t OTYPER;   // GPIO port output type register       (0x04)
    volatile uint32_t OSPEEDR;  // GPIO port output speed register      (0x08)
    volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register (0x0C)
    volatile uint32_t IDR;      // GPIO port input data register        (0x10)
    volatile uint32_t ODR;      // GPIO port output data register       (0x14)
    volatile uint32_t BSRR;     // GPIO port bit set/reset register     (0x18)
    volatile uint32_t LCKR;     // GPIO port configuration lock register(0x1C)
    volatile uint32_t AFRL;     // GPIO alternate function low register (0x20)
    volatile uint32_t AFRH;     // GPIO alternate function high register(0x24)
} GPIO_RegDef_t;

/*GPIO POINTER
 *
 */
#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF   ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG   ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH   ((GPIO_RegDef_t*)GPIOH_BASEADDR)



/* RCC BASE ADDRESS
 *
 */

#define RCC_BASEADDR   0x40023800U





////////////////////////////


typedef struct
{
	volatile uint32_t CR;            // RCC clock control register                    (0x00)
    volatile uint32_t PLLCFGR;       // RCC PLL configuration register                (0x04)
    volatile uint32_t CFGR;          // RCC clock configuration register              (0x08)
    volatile uint32_t CIR;           // RCC clock interrupt register                  (0x0C)
    volatile uint32_t AHB1RSTR;      // RCC AHB1 peripheral reset register            (0x10)
    volatile uint32_t AHB2RSTR;      // RCC AHB2 peripheral reset register            (0x14)
    volatile uint32_t AHB3RSTR;      // RCC AHB3 peripheral reset register            (0x18)
    volatile uint32_t RESERVED0;     // Reserved                                      (0x1C)
       volatile uint32_t APB1RSTR;      // RCC APB1 peripheral reset register            (0x20)
       volatile uint32_t APB2RSTR;      // RCC APB2 peripheral reset register            (0x24)
       volatile uint32_t RESERVED1[2];  // Reserved                                      (0x28-0x2C)
       volatile uint32_t AHB1ENR;       // RCC AHB1 peripheral clock enable register     (0x30)
       volatile uint32_t AHB2ENR;       // RCC AHB2 peripheral clock enable register     (0x34)
       volatile uint32_t AHB3ENR;       // RCC AHB3 peripheral clock enable register     (0x38)
       volatile uint32_t RESERVED2;     // Reserved                                      (0x3C)
       volatile uint32_t APB1ENR;       // RCC APB1 peripheral clock enable register     (0x40)
       volatile uint32_t APB2ENR;       // RCC APB2 peripheral clock enable register     (0x44)
       volatile uint32_t RESERVED3[2];  // Reserved                                      (0x48-0x4C)
           volatile uint32_t AHB1LPENR;     // RCC AHB1 peripheral clock enable in low power (0x50)
           volatile uint32_t AHB2LPENR;     // RCC AHB2 peripheral clock enable in low power (0x54)
           volatile uint32_t AHB3LPENR;     // RCC AHB3 peripheral clock enable in low power (0x58)
           volatile uint32_t RESERVED4;     // Reserved                                      (0x5C)
           volatile uint32_t APB1LPENR;     // RCC APB1 peripheral clock enable in low power (0x60)
           volatile uint32_t APB2LPENR;     // RCC APB2 peripheral clock enable in low power (0x64)
           volatile uint32_t RESERVED5[2];  // Reserved                                      (0x68-0x6C)

           volatile uint32_t BDCR;          // RCC Backup domain control register            (0x70)
               volatile uint32_t CSR;           // RCC clock control & status register           (0x74)
               volatile uint32_t RESERVED6[2];  // Reserved                                      (0x78-0x7C)
               volatile uint32_t SSCGR;         // RCC spread spectrum clock generation register (0x80)
               volatile uint32_t PLLI2SCFGR;    // RCC PLLI2S configuration register             (0x84)
               volatile uint32_t PLLSAICFGR;    // RCC PLLSAI configuration register             (0x88)
               volatile uint32_t DCKCFGR;       // RCC Dedicated Clocks configuration register   (0x8C)
               volatile uint32_t CKGATENR;      // RCC clocks gated enable register              (0x90)
               volatile uint32_t DCKCFGR2;      // RCC Dedicated Clocks configuration register 2 (0x94)
           } RCC_RegDef_t;



         /* RCC POINTER
          *
          */


#define RCC  ((RCC_RegDef_t*)RCC_BASEADDR)

 /* CLOCKA ENABLE MACROS AHB1 bus for GPIOS
  *
  */



#define GPIOA_CLK_EN() (RCC->AHB1ENR |=(1<<0))
#define GPIOB_CLK_EN() (RCC->AHB1ENR |=(1<<1))
#define GPIOC_CLK_EN() (RCC->AHB1ENR |=(1<<2))
#define GPIOD_CLK_EN() (RCC->AHB1ENR |=(1<<3))
#define GPIOE_CLK_EN() (RCC->AHB1ENR |=(1<<4))
#define GPIOF_CLK_EN() (RCC->AHB1ENR |=(1<<5))
#define GPIOG_CLK_EN() (RCC->AHB1ENR |=(1<<6))
#define GPIOH_CLK_EN() (RCC->AHB1ENR |=(1<<7))








 /* ADC BASE ADDRESSES (APB2 bus) */
#define ADC1_BASEADDR   0x40012000U
#define ADC2_BASEADDR   0x40012100U
#define ADC3_BASEADDR   0x40012200U

/* ADC REGISTER STRUCTURE */
typedef struct {
    volatile uint32_t SR;      // Status register           (0x00)
    volatile uint32_t CR1;     // Control register 1        (0x04)
    volatile uint32_t CR2;     // Control register 2        (0x08)
    volatile uint32_t SMPR1;   // Sample time register 1    (0x0C)
    volatile uint32_t SMPR2;   // Sample time register 2    (0x10)
    volatile uint32_t JOFR1;   // Injected channel offset 1 (0x14)
    volatile uint32_t JOFR2;   // Injected channel offset 2 (0x18)
    volatile uint32_t JOFR3;   // Injected channel offset 3 (0x1C)
    volatile uint32_t JOFR4;   // Injected channel offset 4 (0x20)
    volatile uint32_t HTR;     // Watchdog high threshold   (0x24)
    volatile uint32_t LTR;     // Watchdog low threshold    (0x28)
    volatile uint32_t SQR1;    // Regular sequence register 1 (0x2C)
    volatile uint32_t SQR2;    // Regular sequence register 2 (0x30)
    volatile uint32_t SQR3;    // Regular sequence register 3 (0x34)
    volatile uint32_t JSQR;    // Injected sequence register (0x38)
    volatile uint32_t JDR1;    // Injected data register 1   (0x3C)
    volatile uint32_t JDR2;    // Injected data register 2   (0x40)
    volatile uint32_t JDR3;    // Injected data register 3   (0x44)
    volatile uint32_t JDR4;    // Injected data register 4   (0x48)
    volatile uint32_t DR;      // Regular data register      (0x4C)
} ADC_RegDef_t;


/* ADC POINTERS */
#define ADC1   ((ADC_RegDef_t*)ADC1_BASEADDR)
#define ADC2   ((ADC_RegDef_t*)ADC2_BASEADDR)
#define ADC3   ((ADC_RegDef_t*)ADC3_BASEADDR)

/* Clock Enable Macro for ADC1/2/3 (APB2ENR bit 8,9,10) */
#define ADC1_CLK_EN()   (RCC->APB2ENR |= (1<<8))
#define ADC2_CLK_EN()   (RCC->APB2ENR |= (1<<9))
#define ADC3_CLK_EN()   (RCC->APB2ENR |= (1<<10))




#endif /* STM32F446XX_H_ */
