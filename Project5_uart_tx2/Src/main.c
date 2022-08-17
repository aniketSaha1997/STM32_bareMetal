#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN 	(1U<<0)
#define UART2EN 	(1U<<17)

#define SYS_FREQ	16000000
#define APB1_CLK	SYS_FREQ

#define CR1_TE		(1U<<3)
#define CR1_UE		(1U<<13)
#define SR_TXE		(1U<<7)

#define UART_BAUDRATE	115200

static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t BaudRate);
void uart2_tx_init(void);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
int main(void)
{
	 uart2_tx_init();


	while(1)
	{

		printf("Hello From Stm32F4..\n\r");

	}
}

void uart2_tx_init(void){
	/********Configure uart gpio*********/

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA-> MODER |= (1U<<5);
	GPIOA-> MODER &= ~(1U<<4);

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	RCC->APB1ENR |= UART2EN;

	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);


	USART2->CR1 = CR1_TE;
	USART2->CR1 |= CR1_UE;

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t BaudRate)
{

	USARTx-> BRR = compute_uart_bd(periphClk,BaudRate);
}
static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t BaudRate)
{
	return ((periphClk + (BaudRate/2U))/BaudRate);
}
void uart2_write(int ch)
{
	while(!(USART2->SR & SR_TXE))
	{}

	USART2->DR = (ch & 0xFF);

}
