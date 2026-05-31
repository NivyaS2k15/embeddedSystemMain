/*
 * stm32f446xx.h
 * Device header file for STM32F446xx MCU
 * Reference Manual: RM0390
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stddef.h>
#include <stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))

/**********************************START:Processor Specific Details **********************************/
#define NVIC_ISER0          ( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1          ( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2          ( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3          ( (__vo uint32_t*)0xE000E10C )

#define NVIC_ICER0          ((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1          ((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2          ((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3          ((__vo uint32_t*)0xE000E18C)

#define NVIC_PR_BASE_ADDR   ((__vo uint32_t*)0xE000E400)
#define NO_PR_BITS_IMPLEMENTED  4

/**********************************START: Memory Base Addresses **********************************/
#define FLASH_BASEADDR                      0x08000000U
#define SRAM1_BASEADDR                      0x20000000U
#define SRAM2_BASEADDR                      0x2001C000U
#define ROM_BASEADDR                        0x1FFF0000U
#define SRAM                                SRAM1_BASEADDR

/**********************************START: Bus Domain Base Addresses **********************************/
#define PERIPH_BASEADDR                     0x40000000U
#define APB1PERIPH_BASEADDR                 PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR                 0x40100000U
#define AHB1PERIPH_BASEADDR                 0x40020000U
#define AHB2PERIPH_BASEADDR                 0x50000000U
#define AHB3PERIPH_BASEADDR                 0xA0000000U

/**********************************START: AHB1 Peripheral Base Addresses **********************************/
#define GPIOA_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR                      (AHB1PERIPH_BASEADDR + 0x1C00)

#define CRC_BASEADDR                        (AHB1PERIPH_BASEADDR + 0x3000)
#define RCC_BASEADDR                        (AHB1PERIPH_BASEADDR + 0x3800)
#define FLASH_IF_BASEADDR                   (AHB1PERIPH_BASEADDR + 0x3C00)
#define BKPSRAM_BASEADDR                    (AHB1PERIPH_BASEADDR + 0x4000)
#define DMA1_BASEADDR                       (AHB1PERIPH_BASEADDR + 0x6000)
#define DMA2_BASEADDR                       (AHB1PERIPH_BASEADDR + 0x6400)

/**********************************START: APB1 Peripheral Base Addresses **********************************/
#define USART2_BASEADDR                     (APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR                     (APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR                      (APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR                      (APB1PERIPH_BASEADDR + 0x5000)

/**********************************START: APB2 Peripheral Base Addresses **********************************/
#define USART1_BASEADDR                     (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR                     (APB2PERIPH_BASEADDR + 0x1400)
#define SYSCFG_BASEADDR                     (APB2PERIPH_BASEADDR + 0x3800)
#define EXTI_BASEADDR                       (APB2PERIPH_BASEADDR + 0x3C00)

/**********************************Peripheral Register Definition Structures **********************************/
typedef struct
{
    __vo uint32_t MODER;
    __vo uint32_t OTYPER;
    __vo uint32_t OSPEEDR;
    __vo uint32_t PUPDR;
    __vo uint32_t IDR;
    __vo uint32_t ODR;
    __vo uint32_t BSRR;
    __vo uint32_t LCKR;
    __vo uint32_t AFR[2];
} GPIO_RegDef_t;

typedef struct
{
    __vo uint32_t CR;
    __vo uint32_t PLLCFGR;
    __vo uint32_t CFGR;
    __vo uint32_t CIR;
    __vo uint32_t AHB1RSTR;
    __vo uint32_t AHB2RSTR;
    __vo uint32_t AHB3RSTR;
    uint32_t      RESERVED0;
    __vo uint32_t APB1RSTR;
    __vo uint32_t APB2RSTR;
    uint32_t      RESERVED1[2];
    __vo uint32_t AHB1ENR;
    __vo uint32_t AHB2ENR;
    __vo uint32_t AHB3ENR;
    uint32_t      RESERVED2;
    __vo uint32_t APB1ENR;
    __vo uint32_t APB2ENR;
    uint32_t      RESERVED3[2];
    __vo uint32_t AHB1LPENR;
    __vo uint32_t AHB2LPENR;
    __vo uint32_t AHB3LPENR;
    uint32_t      RESERVED4;
    __vo uint32_t APB1LPENR;
    __vo uint32_t APB2LPENR;
    uint32_t      RESERVED5[2];
    __vo uint32_t BDCR;
    __vo uint32_t CSR;
    uint32_t      RESERVED6[2];
    __vo uint32_t SSCGR;
    __vo uint32_t PLLI2SCFGR;
    __vo uint32_t PLLSAICFGR;
    __vo uint32_t DCKCFGR;
    __vo uint32_t CKGATENR;
    __vo uint32_t DCKCFGR2;
} RCC_RegDef_t;

typedef struct
{
    __vo uint32_t IMR;
    __vo uint32_t EMR;
    __vo uint32_t RTSR;
    __vo uint32_t FTSR;
    __vo uint32_t SWIER;
    __vo uint32_t PR;
} EXTI_RegDef_t;

typedef struct
{
    __vo uint32_t MEMRMP;
    __vo uint32_t PMC;
    __vo uint32_t EXTICR[4];
    uint32_t      RESERVED1[2];
    __vo uint32_t CMPCR;
    uint32_t      RESERVED2[2];
    __vo uint32_t CFGR;
} SYSCFG_RegDef_t;

typedef struct
{
    __vo uint32_t SR;
    __vo uint32_t DR;
    __vo uint32_t BRR;
    __vo uint32_t CR1;
    __vo uint32_t CR2;
    __vo uint32_t CR3;
    __vo uint32_t GTPR;
} USART_RegDef_t;


#define I2C1_BASEADDR                       (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR                       (APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR                       (APB1PERIPH_BASEADDR + 0x5C00)
#define FMPI2C1_BASEADDR                    (APB1PERIPH_BASEADDR + 0x6000)
/*
 * Peripheral register definition structure for I2C
 */
typedef struct
{
    __vo uint32_t CR1;                      /*!< I2C control register 1,                        Address offset: 0x00 */
    __vo uint32_t CR2;                      /*!< I2C control register 2,                        Address offset: 0x04 */
    __vo uint32_t OAR1;                     /*!< I2C own address register 1,                    Address offset: 0x08 */
    __vo uint32_t OAR2;                     /*!< I2C own address register 2,                    Address offset: 0x0C */
    __vo uint32_t DR;                       /*!< I2C data register,                             Address offset: 0x10 */
    __vo uint32_t SR1;                      /*!< I2C status register 1,                         Address offset: 0x14 */
    __vo uint32_t SR2;                      /*!< I2C status register 2,                         Address offset: 0x18 */
    __vo uint32_t CCR;                      /*!< I2C clock control register,                    Address offset: 0x1C */
    __vo uint32_t TRISE;                    /*!< I2C TRISE register,                            Address offset: 0x20 */
    __vo uint32_t FLTR;                     /*!< I2C FLTR register,                             Address offset: 0x24 */
} I2C_RegDef_t;


#define I2C1                                ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2                                ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3                                ((I2C_RegDef_t*)I2C3_BASEADDR)

/*
 * Clock Enable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()                      (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()                      (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()                      (RCC->APB1ENR |= (1 << 23))
#define FMPI2C1_PCLK_EN()                   (RCC->APB1ENR |= (1 << 24))


/*
 * Clock Disable Macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()                      (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()                      (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()                      (RCC->APB1ENR &= ~(1 << 23))
#define FMPI2C1_PCLK_DI()                   (RCC->APB1ENR &= ~(1 << 24))


/*
  * Macros to reset I2Cx peripherals
 */
#define I2C1_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)


/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE                          0
#define I2C_CR1_SMBUS                       1
#define I2C_CR1_SMBTYPE                     3
#define I2C_CR1_ENARP                       4
#define I2C_CR1_ENPEC                       5
#define I2C_CR1_ENGC                        6
#define I2C_CR1_NOSTRETCH                   7
#define I2C_CR1_START                       8
#define I2C_CR1_STOP                        9
#define I2C_CR1_ACK                         10
#define I2C_CR1_POS                         11
#define I2C_CR1_PEC                         12
#define I2C_CR1_ALERT                       13
#define I2C_CR1_SWRST                       15


/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ                        0
#define I2C_CR2_ITERREN                     8
#define I2C_CR2_ITEVTEN                     9
#define I2C_CR2_ITBUFEN                     10
#define I2C_CR2_DMAEN                       11
#define I2C_CR2_LAST                        12

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0                       0
#define I2C_OAR1_ADD71                      1
#define I2C_OAR1_ADD98                      8
#define I2C_OAR1_ADDMODE                    15

/*
 * Bit position definitions I2C_SR1
 */
#define I2C_SR1_SB                          0
#define I2C_SR1_ADDR                        1
#define I2C_SR1_BTF                         2
#define I2C_SR1_ADD10                       3
#define I2C_SR1_STOPF                       4
#define I2C_SR1_RXNE                        6
#define I2C_SR1_TXE                         7
#define I2C_SR1_BERR                        8
#define I2C_SR1_ARLO                        9
#define I2C_SR1_AF                          10
#define I2C_SR1_OVR                         11
#define I2C_SR1_PECERR                      12
#define I2C_SR1_TIMEOUT                     14
#define I2C_SR1_SMBALERT                    15

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL                         0
#define I2C_SR2_BUSY                        1
#define I2C_SR2_TRA                         2
#define I2C_SR2_GENCALL                     4
#define I2C_SR2_SMBDEFAULT                  5
#define I2C_SR2_SMBHOST                     6
#define I2C_SR2_DUALF                       7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR                         0
#define I2C_CCR_DUTY                        14
#define I2C_CCR_FS                          15

#define FLAG_SET    1
#define FLAG_RESET  0
#define GPIOA                               ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB                               ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC                               ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD                               ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE                               ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF                               ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG                               ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH                               ((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC                                 ((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI                                ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG                              ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define USART1                              ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2                              ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3                              ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4                               ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5                               ((USART_RegDef_t*)UART5_BASEADDR)
#define USART6                              ((USART_RegDef_t*)USART6_BASEADDR)

/**********************************Clock Enable Macros **********************************/
#define GPIOA_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()                     (RCC->AHB1ENR |= (1 << 7))

#define USART1_PCLK_EN()                    (RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()                    (RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()                    (RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()                     (RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()                     (RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()                    (RCC->APB2ENR |= (1 << 5))

#define USART1_PCCK_EN()                    USART1_PCLK_EN()
#define USART2_PCCK_EN()                    USART2_PCLK_EN()
#define USART3_PCCK_EN()                    USART3_PCLK_EN()
#define UART4_PCCK_EN()                     UART4_PCLK_EN()
#define UART5_PCCK_EN()                     UART5_PCLK_EN()
#define USART6_PCCK_EN()                    USART6_PCLK_EN()

#define SYSCFG_PCLK_EN()                    (RCC->APB2ENR |= (1 << 14))

/**********************************Clock Disable Macros **********************************/
#define GPIOA_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()                     (RCC->AHB1ENR &= ~(1 << 7))

#define USART2_PCLK_DI()                    (RCC->APB1ENR &= ~(1 << 17))

/**********************************Peripheral Reset Macros **********************************/
#define GPIOA_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOF_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); }while(0)
#define GPIOG_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); }while(0)
#define GPIOH_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

#define GPIO_BASEADDR_TO_CODE(x)            ( (x == GPIOA) ? 0 :\
                                              (x == GPIOB) ? 1 :\
                                              (x == GPIOC) ? 2 :\
                                              (x == GPIOD) ? 3 :\
                                              (x == GPIOE) ? 4 :\
                                              (x == GPIOF) ? 5 :\
                                              (x == GPIOG) ? 6 :\
                                              (x == GPIOH) ? 7 : 0 )

/********************************** Bit Definitions **********************************/
#define USART_CR1_RE                     2
#define USART_CR1_TE                     3
#define USART_CR1_IDLEIE                 4
#define USART_CR1_RXNEIE                 5
#define USART_CR1_TCIE                   6
#define USART_CR1_TXEIE                  7
#define USART_CR1_PEIE                   8
#define USART_CR1_PS                     9
#define USART_CR1_PCE                    10
#define USART_CR1_WAKE                   11
#define USART_CR1_M                      12
#define USART_CR1_UE                     13
#define USART_CR1_OVER8                  15

#define USART_CR2_STOP                   12

#define USART_CR3_RTSE                   8
#define USART_CR3_CTSE                   9



#define USART_SR_TC                      6

/* Functional States */
#define ENABLE                           1
#define DISABLE                          0
#define SET                              ENABLE
#define RESET                            DISABLE
#define GPIO_PIN_SET                     ENABLE
#define GPIO_PIN_RESET                   DISABLE

#endif /* INC_STM32F446XX_H_ */
