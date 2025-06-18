#ifndef UART_H
#define UART_H

void UART1_Init(void);
void UART1_SendChar(char c);
char UART1_ReadChar(void);
void UART1_SendString(const char *str);
void SystemClock72MHz(void);
#endif
