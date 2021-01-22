#include <stdint.h>

void UART_Init(unsigned int baud);
void UART_Send(uint8_t* bytes, uint8_t len);
uint8_t UART_onReceive();