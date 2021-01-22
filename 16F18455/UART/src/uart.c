#include "src/uart.h"

void UART_Init(unsigned int baud) {
    // Set baudrate generator
    // TODO This has overflow problems.
    // SP1BRG = (unsigned int) _XTAL_FREQ / (64 * baud) - 1;
    SP1BRG = 51;    // 9600 baud
    // Enable receive interrupts
    RC1IE = 1;
    // Asynchronous mode
    TX1STAbits.SYNC = 0;
    // Enable transmit
    TX1STAbits.TXEN = 1;
    // Enable receive
    RC1STAbits.CREN = 1;
    // Enable module
    RC1STAbits.SPEN = 1;
}

void UART_Send(uint8_t* bytes, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        TX1REG = bytes[i];
        while(!TX1STAbits.TRMT);
    }
}

uint8_t UART_onReceive() {
    // Call this function inside ISR()
    if (RC1IF) {
        uint8_t data = 0x00;
        data = RC1REG;
        RC1IF = 0;
        return data;
    }
    return 0;
}