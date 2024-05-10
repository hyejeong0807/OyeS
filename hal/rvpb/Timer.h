#ifndef HAL_RVPB_TIMER_H_
#define HAL_RVPB_TIMER_H_

typedef union TimerXControl_t
{
    uint32_t all;
    struct {
        uint32_t OneShot:1;     // 0   (1이면 타이머 인터럽트가 한 번 발생하고 타이머가 바로 꺼진다, 다시 켜려면 수동으로 설정)
        uint32_t TimerSize:1;   // 1   (timerxload, timerxvalue의 크기를 설정한다. 0이면 16비트만 사용하고 1이면 32비트를 사용한다)
        uint32_t TimerPre:2;    // 3:2 (클럭마다 카운터를 줄일지, 16번마다 줄일지, 256번마다 줄일지 설정)
        uint32_t Reserved0:1;   // 4   
        uint32_t IntEnable:1;   // 5    
        uint32_t TimerMode:1;   // 6
        uint32_t TimerEn:1;     // 7
        uint32_t Reserved1:24l  // 31:8
    } bits;
} TimerXControl_t;          // 타이머 하드웨어의 속성

typedef union TimerXRIS_t
{
    uint32_t all;
    struct {
        uint32_t TimerXRIS:1;   // 0
        uint32_t Reserved:31;   //31:1
    } bits;
} TimerXRIS_t;

typedef union TimerXMIS_t
{
    uint32_t all;
    struct {
        uint32_t TimerXMIS:1;   // 0
        uint32_t Reserved:31;   // 31:1
    } bits;
} TimerXMIS_t;

typedef struct Timer_t
{
    uint32_t        timerxload;        // 0x00 (카운터의 목표 값을 지정하는 레지스터)
    uint32_t        timerxvalue;       // 0x04 (감소하는 레지스터)
    TimerXControl_t timerxcontrol;     // 0x08 (타이머 하드웨어의 속성을 설정하는 레지스터)
    uint32_t        timerxintclr;      // 0x0C (인터럽트 처리가 완료되었음을 타이머 하드웨어에 알려주는 레지스터)
    TimerXRIS_t     timerxris;         // 0x10 
    TimerXMIS_t     timerxmis;         // 0x14
    uint32_t        timerxbgload;      // 0x18
} Timer_t;

#define TIMER_CPU_BASE 0x10011000
#define TIMER_INTERRUPT 36

#define TIMER_FREERUNNING   0
#define TIMER_PERIOIC       1

#define TIMER_16BIT_COUNTER 0
#define TIMER_32BIT_COUNTER 1

#define TIMER_1MZ_INTERVAL      (1024 * 1024)

#endif /* HAL_RVPB_TIMER_H_ */