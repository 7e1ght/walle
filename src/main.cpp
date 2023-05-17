#include "stm32f10x.h"

void delay(uint32_t msec) 
{
    for(uint32_t i = 0; i < 2000UL*msec; ++i)
    {
        __NOP();
    }
}

int main() 
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH = 0x00;

    GPIOA->CRH |= (1<<8);
    GPIOA->CRH |= (0<<10);

    while(1)
    {
        // GPIOA->BSRR = GPIO_BSRR_BR10;
        // delay(500);

        GPIOA->BSRR = GPIO_BSRR_BS10;
        delay(500);
    } 

    return 0;
}