#include "stm32f446xx_rcc_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB1_PreScaler[4] = {2,4,8,16};

uint32_t RCC_GetPCLK1Value(void)
{
    uint32_t pclk1, SystemClk = 16000000; // Reset fallback to HSI 16MHz
    uint8_t clksrc, temp, ahbp, apb1p;

    clksrc = ((RCC->CFGR >> 2) & 0x3);
    if(clksrc == 0)      { SystemClk = 16000000; }
    else if(clksrc == 1) { SystemClk = 8000000; }

    temp = ((RCC->CFGR >> 4) & 0xF);
    ahbp = (temp < 8) ? 1 : AHB_PreScaler[temp-8];

    temp = ((RCC->CFGR >> 10) & 0x7);
    apb1p = (temp < 4) ? 1 : APB1_PreScaler[temp-4];

    pclk1 = (SystemClk / ahbp) / apb1p;
    return pclk1;
}

uint32_t RCC_GetPCLK2Value(void)
{
    uint32_t SystemClock = 16000000, tmp, pclk2;
    uint8_t clk_src = (RCC->CFGR >> 2) & 0X3;
    uint8_t ahbp, apb2p;

    if(clk_src == 0)      { SystemClock = 16000000; }
    else if(clk_src == 1) { SystemClock = 8000000; }

    tmp = (RCC->CFGR >> 4) & 0xF;
    ahbp = (tmp < 8) ? 1 : AHB_PreScaler[tmp-8];

    tmp = (RCC->CFGR >> 13) & 0x7;
    apb2p = (tmp < 4) ? 1 : APB1_PreScaler[tmp-4];

    pclk2 = (SystemClock / ahbp) / apb2p;
    return pclk2;
}
