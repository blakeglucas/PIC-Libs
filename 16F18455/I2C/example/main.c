/*
 * File:   main.c
 * Author: Blake Lucas
 *
 * Simple I2C Example to read the ID of a VCNL4200 sensor
 */

#include <xc.h>

#include "src/i2c.h"

#define PPS_UNLOCK      PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCK = 0x00
#define PPS_LOCK        PPSLOCK = 0x55; PPSLOCK = 0xAA; PPSLOCK = 0x01

void main(void) {
    GIE = 0;
    PPS_UNLOCK;
    
    // PPS Setting for SDA/SCL
    RC2PPS = 0x14;
    RC3PPS = 0x13;
    SSP1DATPPS = 0x12;
    SSP1CLKPPS = 0x13;
    
    PPS_LOCK;
    PEIE = 1;
    GIE = 1;
    
    ANSELC = 0x00;

    uint8_t high, low;
    
    I2C_Init();
    I2C_Start();
    I2C_Write(W(0x51));
    I2C_Write(0x0E);
    I2C_Restart();
    I2C_Write(R(0x51));
    low = I2C_Read();
    I2C_AckN(0);
    high = I2C_Read();
    I2C_AckN(0);
    I2C_Stop();
    __delay_ms(100);
    
    // Breakpoint here to check results (high and low)
    asm("nop");
    return;
}