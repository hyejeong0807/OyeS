#include "armcpu.h"

void enable_irq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("BIC r1, r0, #0x80");  // 0x80: cpsr의 IRQ 마스크 비트 위치인 7번째가 1로 셋
    __asm__ ("MSR cpsr, r1");       // BIC를 사용하면 1이 있는 비트에 0을 쓴다.
    __asm__ ("POP {r0, r1}");
}

void enable_fiq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("BIC r1, r0, #0x40");  // 0x40: cpsr의 FIQ 마스크 비트 위치인 6번째가 1로 셋
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void disable_irq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("ORR r1, r0, #0x80");  // ORR을 사용하면 해당 비트에 1을 설정한다.
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void disable_fiq(void)
{
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("ORR r1, r0, #0x40");
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}