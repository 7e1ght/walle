extern void* _estack;

void Reset_Handler();
void NMI_Handler();
void HardFault_Handler();
void MemManage_Handler();
void BusFault_Handler();
void UsageFault_Handler();
void SVC_Handler();
void DebugMon_Handler();
void PendSV_Handler();
void SysTick_Handler();
void WWDG_Handler();
void PVD_Handler();
void AMPER_Handler();
void RTC_Handler();
void FLASH_Handler();
void RCC_Handler();
void EXTI0_Handler();
void EXTI1_Handler();
void EXTI2_Handler();
void EXTI3_Handler();
void EXTI4_Handler();
void DMA1_Channel1_Handler();
void DMA1_Channel2_Handler();
void DMA1_Channel3_Handler();
void DMA1_Channel4_Handler();
void DMA1_Channel5_Handler();
void DMA1_Channel6_Handler();
void DMA1_Channel7_Handler();
void ADC1_2_Handler();
void USB_HP_CAN_TX_Handler();
void USB_LP_CAN_RX0_Handler();
void CAN_RX1_Handler();
void CAN_SCE_Handler();
void EXTI9_5_Handler();
void TIM1_BRK_Handler();
void TIM1_UP_Handler();
void TIM1_TRG_COM_Handler();
void TIM1_CC_Handler();
void TIM2_Handler();
void TIM3_Handler();
void TIM4_Handler();
void I2C1_EV_Handler();
void I2C1_ER_Handler();
void I2C2_EV_Handler();
void I2C2_ER_Handler();
void SPI1_Handler();
void SPI2_Handler();
void USART1_Handler();
void USART2_Handler();
void USART3_Handler();
void EXTI15_10_Handler();
void RTCAlarm_Handler();
void USBWakeup_Handler();
void TIM8_BRK_Handler();
void TIM8_UP_Handler();
void TIM8_TRG_COM_Handler();
void TIM8_CC_Handler();
void ADC3_Handler();
void FSMC_Handler();
void SDIO_Handler();
void TIM5_Handler();
void SPI3_Handler();
void UART4_Handler();
void UART5_Handler();
void TIM6_Handler();
void TIM7_Handler();
void DMA2_Channel1_Handler();
void DMA2_Channel2_Handler();
void DMA2_Channel3_Handler();
void DMA2_Channel4_5_Handler();

int  main();

void *_vectors[] __attribute__((section(".isr_vector"), used)) = {
    &_estack,
    &Reset_Handler,
    &NMI_Handler,
    &HardFault_Handler,
    &MemManage_Handler,
    &BusFault_Handler,
    &UsageFault_Handler,
    0,
    0,
    0,
    0,
    &SVC_Handler,
    &DebugMon_Handler,
    0,
    &PendSV_Handler,
    &SysTick_Handler,
    &WWDG_Handler,
    &PVD_Handler,
    &AMPER_Handler,
    &RTC_Handler,
    &FLASH_Handler,
    &RCC_Handler,
    &EXTI0_Handler,
    &EXTI1_Handler,
    &EXTI2_Handler,
    &EXTI3_Handler,
    &EXTI4_Handler,
    &DMA1_Channel1_Handler,
    &DMA1_Channel2_Handler,
    &DMA1_Channel3_Handler,
    &DMA1_Channel4_Handler,
    &DMA1_Channel5_Handler,
    &DMA1_Channel6_Handler,
    &DMA1_Channel7_Handler,
    &ADC1_2_Handler,
    &USB_HP_CAN_TX_Handler,
    &USB_LP_CAN_RX0_Handler,
    &CAN_RX1_Handler,
    &CAN_SCE_Handler,
    &EXTI9_5_Handler,
    &TIM1_BRK_Handler,
    &TIM1_UP_Handler,
    &TIM1_TRG_COM_Handler,
    &TIM1_CC_Handler,
    &TIM2_Handler,
    &TIM3_Handler,
    &TIM4_Handler,
    &I2C1_EV_Handler,
    &I2C1_ER_Handler,
    &I2C2_EV_Handler,
    &I2C2_ER_Handler,
    &SPI1_Handler,
    &SPI2_Handler,
    &USART1_Handler,
    &USART2_Handler,
    &USART3_Handler,
    &EXTI15_10_Handler,
    &RTCAlarm_Handler,
    &USBWakeup_Handler,
    &TIM8_BRK_Handler,
    &TIM8_UP_Handler,
    &TIM8_TRG_COM_Handler,
    &TIM8_CC_Handler,
    &ADC3_Handler,
    &FSMC_Handler,
    &SDIO_Handler,
    &TIM5_Handler,
    &SPI3_Handler,
    &UART4_Handler,
    &UART5_Handler,
    &TIM6_Handler,
    &TIM7_Handler,
    &DMA2_Channel1_Handler,
    &DMA2_Channel2_Handler,
    &DMA2_Channel3_Handler,
    &DMA2_Channel4_5_Handler
};

extern void *_sidata, *_sdata, *_edata, *_sbss, *_ebss;

void __attribute__((naked, noreturn)) Reset_Handler()
{
    void **pSource, **pDest;
    for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
        *pDest = *pSource;

    for (pDest = &_sbss; pDest != &_ebss; pDest++)
        *pDest = 0;

    main();

    while(1);
}

void __attribute__((naked, noreturn))  NMI_Handler()        {}
void __attribute__((naked, noreturn))  HardFault_Handler()  {}
void __attribute__((naked, noreturn))  MemManage_Handler()  {}
void __attribute__((naked, noreturn))  BusFault_Handler()   {}
void __attribute__((naked, noreturn))  UsageFault_Handler() {}
void __attribute__((naked, noreturn))  SVC_Handler()        {}
void __attribute__((naked, noreturn))  DebugMon_Handler()   {}
void __attribute__((naked, noreturn))  PendSV_Handler()     {}
void __attribute__((naked, noreturn))  SysTick_Handler()    {}

