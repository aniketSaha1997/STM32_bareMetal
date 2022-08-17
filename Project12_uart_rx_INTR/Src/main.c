#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"

#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5)

#define LED_PIN		GPIOA_5

char key;

static void uart_callback(void);
int main(void)
{


	 RCC->AHB1ENR |= GPIOAEN;
	 GPIOA->MODER |= (1U<<10);
	 GPIOA->MODER &= ~(1U<<11);

	 uart2_rx_interrupt();

	while(1)
	{




	}
}

static void uart_callback(void)
{
	key= USART2->DR;
			if(key == '1')
				{
					GPIOA->ODR |= LED_PIN;

				}
			else
			{
				GPIOA->ODR &= ~LED_PIN;
			}
}

void USART2_IRQHandler(void){
	if(USART2->SR & SR_RXNE)
	{
		uart_callback();
	}
}
