#include "stm32f10x.h"
#include <stdbool.h>

volatile uint32_t tick = 0;
volatile uint32_t delay_time = 0;

bool show = false;

void SysTick_Handler()
{
    tick++;
    if(delay_time) delay_time--;
}

void serialWireOn()
{
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
	AFIO->MAPR2 = AFIO_MAPR_SWJ_CFG_JTAGDISABLE; // Enable Serial Wire
	
	// Lock PA13, PA14
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);
	GPIOA->LCKR = GPIO_LCKR_LCKK | GPIO_LCKR_LCK13 | GPIO_LCKR_LCK14;
	GPIOA->LCKR = GPIO_LCKR_LCK13 | GPIO_LCKR_LCK14;
	GPIOA->LCKR = GPIO_LCKR_LCKK | GPIO_LCKR_LCK13 | GPIO_LCKR_LCK14;
	GPIOA->LCKR;
}

void initSysTick()
{
	CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);//На всякий случай выключим счетчик
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);//Разрешим прерывания по таймеру
	SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); //Выберем без делителя. будет 72 MHz
	MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, 71999 << SysTick_LOAD_RELOAD_Pos); //Настройка на 1 мс
	MODIFY_REG(SysTick->LOAD, SysTick_VAL_CURRENT_Msk, 71999 << SysTick_VAL_CURRENT_Pos); //Начнем считать с 71999 до 0
	SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //На всякий случай выключим счетчик
}

void delay(uint32_t ms)
{
    delay_time = ms;
    while (delay_time != 0U) {}
}

void initRCC() 
{
	SET_BIT(RCC->CR, RCC_CR_HSEON); //Запустим внутренний RC генератор на 8 МГц
	while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET); //Дождемся поднятия флага о готовности
	
	SET_BIT(RCC->CR, RCC_CR_HSEON); //Запустим внешний кварцевый резонатор. Он у нас на 8 MHz
	while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) ; //Дождемся поднятия флага о готовности
	
	CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); //Сбросим бит байпаса в 0
	
	SET_BIT(RCC->CR, RCC_CR_CSSON); //Запустим Clock detector
	
	//SET_BIT(RCC->CR, RCC_CR_PLLON); //Запустим PLL
	//while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);//Ожидаем готовность включения PLL
	
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL); //Выберем PLL в качестве System clock
	
	MODIFY_REG(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL); //Используем PLL в качестве System_clock
	
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_CFGR_HPRE_DIV1); //AHB Prescaler /1
	
	MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2); //010 Two wait states, if 48 MHz < SYSCLK <= 72 MHz
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE); //1: Prefetch is enabled
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBS); //1: Prefetch buffer is enabled
	
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_CFGR_PPRE1_DIV2); //APB1 Prescaler /2, т.к. PCLR 1 max 36 MHz
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, RCC_CFGR_PPRE2_DIV1); //APB2 Prescaler /1
	
	MODIFY_REG(RCC->CFGR, RCC_CFGR_ADCPRE, RCC_CFGR_ADCPRE_DIV6); //72/6 = 12 Мгц. 14 максимум
	SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC); //В качестве входного сигнала для PLL выберем HSE
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE); //Никакое предделение перед PLL нам не нужно. Поэтому /1
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLMULL, RCC_CFGR_PLLMULL9); //т.к. кварц у нас на 8 MHz, а нам нужно 72, то нужно сделать умножение на 9. 8*9 = 72
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_USBPRE); // Настроили USB на 48 MHz
	MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, RCC_CFGR_MCO_PLL);
	
	SET_BIT(RCC->CR, RCC_CR_PLLON); //Запустим PLL
	while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);//Ожидаем готовность включения PLL
}

void makeStep()
{
	GPIOA->BSRR = GPIO_BSRR_BS10;
	delay(2);
	GPIOA->BSRR = GPIO_BSRR_BR10;
	delay(2);
}

int main() 
{
	serialWireOn();
    initSysTick();
    initRCC();

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

	CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF10);
	SET_BIT(GPIOA->CRH, GPIO_CRH_MODE10);

	CLEAR_BIT(GPIOA->CRH, GPIO_CRH_CNF9);
	SET_BIT(GPIOA->CRH, GPIO_CRH_MODE9);

    while(1)
    {
        makeStep();
    }

    return 0;
}