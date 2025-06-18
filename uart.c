#include "stm32f10x.h"
#include "uart.h"
void SystemClock72MHz(void) {
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9; // HSE x 9 = 72 MHz
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;

    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
void UART1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;    // Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;  // Enable USART1 clock

    // Configure PA9 (TX) as Alternate Function Push-Pull
    GPIOA->CRH &= ~(0xF << 4);             // Clear MODE9 and CNF9
    GPIOA->CRH |=  (0xB << 4);             // MODE9 = 11 (50 MHz), CNF9 = 10 (AF Push-Pull)

    // Configure PA10 (RX) as Floating Input
    GPIOA->CRH &= ~(0xF << 8);             // Clear MODE10 and CNF10
    GPIOA->CRH |=  (0x4 << 8);             // MODE10 = 00, CNF10 = 01 (floating input)

    // Set baud rate: 9600 @ 72 MHz -> USARTDIV = 468.75 -> BRR = 0x1D4C
    USART1->BRR = (468 << 4) | 12;

    // Enable USART1, TX and RX
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UART1_SendChar(char c) {
    while (!(USART1->SR & USART_SR_TXE));  // Wait until TX buffer is empty
    USART1->DR = c;
}

char UART1_ReadChar(void) {
    while (!(USART1->SR & USART_SR_RXNE)); // Wait until data is received
    return USART1->DR;
}

void UART1_SendString(const char *str) {
    while (*str) {
        UART1_SendChar(*str++);
    }
}
