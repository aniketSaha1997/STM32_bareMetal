#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"

#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5)

#define LED_PIN		GPIOA_5

char key;

static void dma_callback(void);
int main(void)
{

	char message[31] = "Hello from Stm32 DMA transfer\n\r";

	 RCC->AHB1ENR |= GPIOAEN;
	 GPIOA->MODER |= (1U<<10);
	 GPIOA->MODER &= ~(1U<<11);

	 uart2_tx_init();
	 dma1_stream6_init((uint32_t) message,(uint32_t)&USART2->DR,31);

	while(1)
	{




	}
}

static void dma_callback(void)
{
	GPIOA-> ODR ^= LED_PIN;
}

void DMA1_Stream6_IRQHandler(void)
{
	//Check for transfer complete interrupt in HISR register
	if(DMA1->HISR & HISR_TCIF6)
	{
		//CLear the flag
		DMA1->HIFCR |= HISR_CTCIF6;

		dma_callback();
	}

}
