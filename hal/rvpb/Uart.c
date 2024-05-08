#include "stdint.h"
#include "Uart.h"
#include "HalUart.h"
#include "HalInterrupt.h"

extern volatile PL011_t* Uart;

static void interrupt_handler(void);

void Hal_uart_init(void)
{
    // Enable UART
    // 하드웨어 컨트롤러 레지스터를 변경하기 전 하드웨어를 꺼놓는 코드
    Uart->uartcr.bits.UARTEN = 0;
    // UART 출력
    Uart->uartcr.bits.TXE = 1;
    // UART 입력
    Uart->uartcr.bits.RXE = 1;
    // 아까 꺼놨던 UART 하드웨어 전체를 다시 켜는 코드
    Uart->uartcr.bits.UARTEN = 1;

    // Enable input interrupt
    Uart->uartimsc.bits.RXIM = 1;

    // Register UART interrupt handler
    Hal_interrupt_enable(UART_INTERRUPT0);
    Hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0);

}

// 알파벳 한 글자를 UART를 통해서 출력하는 코드
void Hal_uart_put_char(uint8_t ch)
{
    // uart 하드웨어의 출력 버퍼가 0이 될 때까지 기다리는 코드
    // 0이라는 말은 버퍼가 비었다는 것을 의미
    while(Uart->uartfr.bits.TXFF);
    // 데이터 레지스터를 통해 알파벳 한 글자를 출력 버퍼로 보내는 코드
    Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void)
{
    uint8_t data;

    while(Uart->uartfr.bits.RXFE);

    // CASE 1
    // Check for an error flag
    // 여기 조건문이 성능이 좋지 않음
    // 왜? if 문에서 각 에러 플래그 4개를 개별적으로 확인하기 때문이다.
    // if (Uart->uartdr.bits.BE || Uart->uartdr.bits.FE ||
    //     Uart->uartdr.bits.OE || Uart->uartdr.bits.PE)
    // {
    //     // Clear the error
    //     Uart->uartrsr.bits.BE = 1;
    //     Uart->uartrsr.bits.FE = 1;
    //     Uart->uartrsr.bits.OE = 1;
    //     Uart->uartrsr.bits.PE = 1;
    //     return 0;
    // }

    // CASE 2
    // if (Uart->uartdr.all & 0xFFFFFF00) {
    //     // Clear the error
    //     Uart->uartrsr.all = 0xFF;
    //     return 0;
    // }

    // data = Uart->uartdr.bits.DATA;
    //return data;

    // CASE 3
    data = Uart->uartdr.all;

    // Check for an error flag
    if (data & 0xFFFFFF00) {
        // Clear the error
        Uart->uartrsr.all = 0xFF;
        return 0;
    }

    return (uint8_t)(data & 0xFF);
}

static void interrupt_handler(void)
{
    uint8_t ch = Hal_uart_get_char();
    Hal_uart_put_char(ch);
}