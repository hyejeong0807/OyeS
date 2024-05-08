#include "stdbool.h"
#include "stdint.h"
#include "HalInterrupt.h"

// attribute? gcc의 컴파일러 확장 기능을 사용하겠다는 지시어
__attribute__ ((interrupt ("IRQ"))) void Irq_Handler(void)
{
    Hal_interrupt_run_handler();
}

__attribute__ ((interrupt ("FIQ"))) void Fiq_Handler(void)
{
    while(true);
}