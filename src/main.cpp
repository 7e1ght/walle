#include "stm32f10x.h"

volatile uint8_t tick = 0;
volatile uint8_t delay_time = 0;

void initSysTick()
{
    SysTick->CTRL &= 0x00; // clock is disable
    SysTick->CTRL |= SysTick_CTRL_TICKINT;
    SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE;

    SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk; 
    SysTick->LOAD |= (71999 << SysTick_LOAD_RELOAD_Pos); 

    SysTick->VAL &= (0x00 << SysTick_VAL_CURRENT_Pos);

    SysTick->CTRL |= SysTick_CTRL_ENABLE;
}

void SysTick_Handler()
{
    tick++;
    if(delay_time) delay_time--;
}

void delay(uint8_t ms)
{
    delay_time = ms;
    while (delay_time != 0);
}

void initRCC() 
{
    RCC->CR &= 0x00;
    RCC->CR |= RCC_CR_HSION;
    while (static_cast<bool>(RCC->CR & RCC_CR_HSIRDY) != SET);

    RCC->CR |= RCC_CR_HSEON;
    while (static_cast<bool>(RCC->CR & RCC_CR_HSERDY) != SET);
    
    RCC->CR &= ~RCC_CR_HSEBYP;
    RCC->CR |= RCC_CR_CSSON;

    RCC->CFGR &= 0x00;

    RCC->CFGR |= RCC_CFGR_SW_PLL;
    RCC->CFGR |= RCC_CFGR_SWS_PLL;
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    FLASH->ACR &= 0x00;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR |= FLASH_ACR_PRFTBS;

    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;
    RCC->CFGR |= RCC_CFGR_PLLXTPRE;
    RCC->CFGR |= RCC_CFGR_PLLMULL9;
    RCC->CFGR &= ~RCC_CFGR_USBPRE;
    RCC->CFGR |= RCC_CFGR_MCO_PLL;

    RCC->CR |= RCC_CR_PLLON;
    while (static_cast<bool>(RCC->CR & RCC_CR_PLLRDY) != SET);
}

int main() 
{
    initRCC();
    initSysTick();

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

    while (1)
    {
        GPIOC->BSRR |= GPIO_BSRR_BS13;
        delay(1000);

        GPIOC->BSRR |= GPIO_BSRR_BR13;
        delay(1000);
    }

    return 0;
}