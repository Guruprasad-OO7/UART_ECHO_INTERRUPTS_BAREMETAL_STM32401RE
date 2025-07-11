#include "stm32f4xx.h"
void UART2_Init(void);
void UART2_SendChar(char c);
volatile char received_char;     // stores incoming char
volatile uint8_t data_ready=0; // flag to indicate reception
int main(void)
{
    UART2_Init();
    while(1)
    {
        if(data_ready)
        {
            UART2_SendChar(received_char); // echo received char
            data_ready=0;                // reset flag
        }
    }
}
void UART2_Init(void)
{
    RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock
    GPIOA->MODER &= ~((3<<(2*2)) | (3<<(3*2)));
    GPIOA->MODER |=(2<<(2*2)) | (2<<(3*2));// Set PA2, PA3 to Alternate Function mode (AF7 for USART2)
    GPIOA->AFR[0] &= ~((0xF<<(2*4)) | (0xF<<(3*4)));
    GPIOA->AFR[0] |= (7<<(2*4)) | (7<<(3*4));
    RCC->APB1ENR |=RCC_APB1ENR_USART2EN; // Enable USART2 clock
    USART2->BRR=0x0683; 
    USART2->CR1 |= USART_CR1_RXNEIE; // RX interrupt enable Enable RX interrupt, RX, TX, and USART
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;  // TX + RX
    USART2->CR1 |= USART_CR1_UE;  // USART enable
    NVIC_EnableIRQ(USART2_IRQn); // Enable USART2 IRQ in NVIC
}
void UART2_SendChar(char c)
{
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR=c;
}
void USART2_IRQHandler(void) // USART2 Interrupt Handler
{
    if (USART2->SR & USART_SR_RXNE)
    {
        received_char=USART2->DR;  // Read received character
        data_ready=1;              // Set flag
    }
}
