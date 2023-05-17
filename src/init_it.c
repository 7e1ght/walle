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

void __attribute__((naked, noreturn))  NMI_Handler() {}
void __attribute__((naked, noreturn))  HardFault_Handler() {}
void __attribute__((naked, noreturn))  MemManage_Handler() {}
void __attribute__((naked, noreturn))  BusFault_Handler() {}
void __attribute__((naked, noreturn))  UsageFault_Handler() {}
void __attribute__((naked, noreturn))  SVC_Handler() {}
void __attribute__((naked, noreturn))  DebugMon_Handler() {}
void __attribute__((naked, noreturn))  PendSV_Handler() {}
void __attribute__((naked, noreturn))  SysTick_Handler() {}