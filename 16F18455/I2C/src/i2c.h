#include <stdint.h>

#ifndef I2C_TIMEOUT
#define I2C_TIMEOUT 1000
#endif

#define W(a)        (a << 1) & 0xFE
#define R(a)        (a << 1) | 0x01

void I2C_Wait();
void I2C_Start();
void I2C_Restart();
void I2C_Stop();
void I2C_AckN(char a);
char I2C_Write(uint8_t data);
uint8_t I2C_Read();