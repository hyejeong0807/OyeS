/**
    태스크 컨트롤 블록과 태스크 관련 API 함수 정의
*/

#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#include "MemoryMap.h"

#define NOT_ENOUGH_TASK_NUM 0xFFFFFFFF

#define USR_TASK_STACK_SIZE 0x100000    // 1MB, 각 태스크별로 1MB씩 스택 할당
#define MAX_TASK_NUM        (TASK_STACK_SIZE / USR_TASK_STACK_SIZE)

typedef struct KernelTaskContext_t  // 컨텍스트를 추상화한 자료 구조
{                                   // ARM의 프로그램 상태 레지스터와 범용 레지스터 백업
    uint32_t spsr;
    uint32_t r0_r12[13];
    uint32_t pc;
} KernelTaskContext_t;

typedef struct KernelTcb_t  // 스택 관련 정보만 가지고 있다.
{
    uint32_t sp;            // 범용 레지스터 (스택 포인터)
    uint8_t* stack_base;    // 컨텍스트에 포함되지 않는 부가 데이터
} KernelTcb_t;

typedef void (*KernelTaskFunc_t)(void);

// 커널 태스크 관련 기능을 초기화하는 함수
void Kernel_task_init(void);
// 커널 태스크를 생성하는 함수
uint32_t Kernel_task_create(KernelTaskFunc_t startFunc);

#endif /* KERNEL_TASK_H_ */