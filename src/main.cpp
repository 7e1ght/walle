#include "stm32f10x.h"

void delay(uint32_t msec) 
{
    for(uint32_t i = 0; i < 250UL*msec; ++i)
    {
        __NOP();
    }
}

int main() 
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH &= 0x00;
    GPIOA->CRH |= GPIO_CRH_MODE10_0;
    GPIOA->CRH |= 0x00;

    while(1)
    {
        GPIOA->BSRR = GPIO_BSRR_BS10;
        delay(1000);

        GPIOA->BSRR = GPIO_BSRR_BR10;
        delay(1000);
    } 

    return 0;
}