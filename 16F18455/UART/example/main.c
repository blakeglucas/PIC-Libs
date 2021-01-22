/*
 * File:   main.c
 * Author: Blake Lucas
 *
 * Simple UART echo application
 */

#include <xc.h>

#include "src/uart.h"

#define PPS_UNLOCK      PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCK = 0x00
#define PPS_LOCK        PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCK = 0x01

void __interrupt() ISR() {
    uint8_t data = UART_onReceive();
    // If you need to be able to receive 0x00, you'll have to
    // rework this logic
    if (data != 0) {
        UART_Send(data, 1);
    }
}

void main(void) {
    GIE = 0;
    PPS_UNLOCK;

    RC0PPS = 0x0F;
    RX1PPS = 0x11;

    PPS_LOCK;
    PEIE = 1;
    GIE = 1;

    ANSELC = 0x00;
    TRISC0 = 1;

    UART_Init(9600);
    __delay_ms(100);
    UART_Send("Hello\r\n", 7);

    while(1);

    return;
}