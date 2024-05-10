#include "stdint.h"
#include "Timer.h"
#include "HalTimer.h"
#include "HalInterrupt.h"

extern volatile Timer_t* Timer;

static void interrupt_handler(void);

static uint32_t internal_1ms_counter;

void Hal_timer_init(void)
{
    // interface reset (타이머 하드웨어 인터페이스 초기화 코드)
    Timer->timerxcontrol.bits.TimerEn = 0;          // 타이머를 끈다
    Timer->timerxcontrol.bits.TimerMode = 0;        // 프리-러닝 모드로 설정한다
    Timer->timerxcontrol.bits.OneShot = 0;          
    Timer->timerxcontrol.bits.TimerSize = 0;        // 16비트 카운터 모드로 설정한다
    Timer->timerxcontrol.bits.TimerPre = 0;         // 프리스케일러 분주 (divider)는 1로 설정한다
    Timer->timerxcontrol.bits.IntEnable = 1;        // 인터럽트를 켠다
    Timer->timerxload = 0;
    Timer->timerxvalue = 0xFFFFFFFF;                // 카운터 레지스터 설정한다

    // set periodic mode (1ms 간격으로 인터럽트를 발생하게 타이머를 설정)
    Timer->timerxcontrol.bits.TimerMode = TIMER_PERIOIC;
    Timer->timerxcontrol.bits.TimerSize = TIMER_32BIT_COUNTER;
    Timer->timerxcontrol.bits.OneShot = 0;
    Timer->timerxcontrol.bits.TimerPre = 0;
    Timer->timerxcontrol.bits.IntEnable = 1;

    uint32_t interval_1ms = TIMER_1MZ_INTERVAL / 1000;

    Timer->timerxload = interval_1ms;
    Timer->timerxcontrol.bits.TimerEn = 1;

    internal_1ms_counter = 0;

    // Register Timer interrupt handler
    Hal_interrupt_enable(TIMER_INTERRUPT);
    Hal_interrupt_register_handler(interrupt_handler, TIMER_INTERRUPT);
}

static void interrupt_handler(void)
{
    internal_1ms_counter++;

    Timer->timerxintclr = 1;
}

uint32_t Hal_timer_get_1ms_counter(void)
{
    return internal_1ms_counter;
}