#include "stdint.h"
#include "HalUart.h"

#include "stdio.h"

static void Hw_init(void);
static void Printf_test(void);

void main(void)
{
	// 하드웨어 초기화 진행
	Hw_init();

	uint32_t i = 100;
	while (i--)
	{
		Hal_uart_put_char('N');
	}
	Hal_uart_put_char('\n');

	putstr("Hello World!\n");

	Printf_test();

	while(true);

	i = 100;
	// 1바이트씩 100번 읽는다는 것을 의미한다.
	// while 조건을 true로 변경하면 계속 에코 기능이 동작한다.
	while (i--) {
		uint8_t ch = Hal_uart_get_char();
		Hal_uart_put_char(ch);
	}
}

static void Hw_init(void)
{
	Hal_interrupt_init();
	Hal_uart_init();
}

static void Printf_test(void)
{
	char* str = "printf pointer test";
	char* nullptr = 0;
	uint32_t i = 5;

	debug_printf("%s\n", "Hello printf");
	debug_printf("output string pointer: %s\n", str);
	debug_printf("%s is null pointer, %u number\n", nullptr, 10);
	debug_printf("%u = 5\n", i);
	debug_printf("dec=%u hex=%x\n", 0xff, 0xff);
	debug_printf("print zero %u\n", 0);
}