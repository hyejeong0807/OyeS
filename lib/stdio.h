#ifndef LIB_STDIO_H_
#define LIB_STDIO_H_

#include "stdarg.h"

typedef enum utoa_t
{
    utoa_dec = 10,
    utoa_hex = 16,
} utoa_t;

uint32_t putstr(const char* s);
uint32_t debug_printf(const char* format, ...);
uint32_t vsprintf(char* buf, const char* format, va_list arg);

// arg1: 리턴 포인터로 사용
// arg2: 문자열로 바꿀 원본 데이터 숫자
// arg3: 문자열을 10진수로 표현할지 16진수로 표현할지
uint32_t utoa(char* buf, uint32_t val, utoa_t base);

#endif /* LIB_STDIO_H_ */