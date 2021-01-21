#include "i2c.h"

void I2C_Wait()
{
    for(int i = 0; i < I2C_TIMEOUT && (SSP1STATbits.R_nW || SSP1CON2 & 0x1f); i++);
}

void I2C_Start()
{
    I2C_Wait();
    SEN1 = 1;
    for(int i = 0; i < I2C_TIMEOUT && SEN1; i++);
}

void I2C_Restart()
{
    I2C_Wait();
    RSEN1 = 1;
    for(int i = 0; i < I2C_TIMEOUT && !SSP1IF; i++);
    SSP1IF = 0;
}

void I2C_Stop()
{
    I2C_Wait();
    PEN1 = 1;
    for(int i = 0; i < I2C_TIMEOUT && !SSP1IF; i++);
    SSP1IF = 0;
}

void I2C_AckN(char a)
{
    I2C_Wait();
    ACKDT1 = a;
    ACKEN1 = 1;
    for(int i = 0; i < I2C_TIMEOUT && ACKEN1; i++);
}

char I2C_Write(uint8_t data)
{
    I2C_Wait();
    SSP1BUF = data;
    for(int i = 0; i < I2C_TIMEOUT && BF1; i++);
    for(int i = 0; i < I2C_TIMEOUT && !SSP1IF; i++);
    SSP1IF = 0;
    return ACKSTAT1;
}

uint8_t I2C_Read()
{
    uint8_t data = 0x00;
    I2C_Wait();
    RCEN1 = 1;
    for(int i = 0; i < I2C_TIMEOUT && !BF1; i++);
    data = SSP1BUF;
    return data;
}