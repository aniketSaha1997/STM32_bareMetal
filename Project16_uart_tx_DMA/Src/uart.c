#include "uart.h"

#define GPIOAEN 	 (1U<<0)
#define UART2EN 	 (1U<<17)

#define SYS_FREQ	 16000000
#define APB1_CLK	 SYS_FREQ

#define CR1_TE		 (1U<<3)
#define CR1_RE		 (1U<<2)

#define CR1_UE		 (1U<<13)
#define SR_TXE		 (1U<<7)
#define SR_RXNE		 (1U<<5)
#define CR1_RXNEIE	 (1U<<5)

#define DMA1EN		 (1U<<21)
#define DMA_S_EN	 (1U<<0)
#define CHSEL4		 (1U<<27)
#define MINC_MODE	 (1U<<10)
#define DMA_DIR		 (1U<<6)
#define DMA_CR_TCIE	 (1U<<4)
#define DMA_CR_EN	 (1U<<0)
#define UART_CR3_DMAT (1U<<7)

#define UART_BAUDRATE	115200


static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t BaudRate);

void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
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

void uart2_rxtx_init(void){
	/********Configure uart gpio*********/

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA-> MODER |= (1U<<5);
	GPIOA-> MODER &= ~(1U<<4);
 /*********PA2 ALternate function mode****/

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	GPIOA-> MODER &= ~(1U<<6);
	GPIOA-> MODER |= (1U<<7);

	/*********PA3 ALternate function mode****/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);



	RCC->APB1ENR |= UART2EN;

	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);


	USART2->CR1 = CR1_TE | CR1_RE;

	USART2->CR1 |= CR1_UE;

}

void dma1_stream6_init(uint32_t src,uint32_t dst,uint32_t len)
{
	//Enable clock access to DMA
	RCC->AHB1ENR |= DMA1EN;

	//Disbale DMA1 stream6
	DMA1_Stream6->CR &= ~DMA_S_EN;

	//Clear all interrupt flags of Stream6
	DMA1->HIFCR |=(1U<<16);
	DMA1->HIFCR |=(1U<<18);
	DMA1->HIFCR |=(1U<<19);
	DMA1->HIFCR |=(1U<<20);
	DMA1->HIFCR |=(1U<<21);

	//Set destination buffer
	DMA1_Stream6->PAR =dst;

	//Set the source buffer
	DMA1_Stream6->M0AR = src;

	//Set length
	DMA1_Stream6->NDTR = len;

	//Select Stream 6 channel 4
	DMA1_Stream6->CR = CHSEL4;

	//Enable memory increment
	DMA1_Stream6->CR |= MINC_MODE;

	//Configure transfer direction
	DMA1_Stream6->CR |= DMA_DIR;

	//Enable DMA  transfer complete interrupt
	DMA1_Stream6->CR |=DMA_CR_TCIE;

	//Enable direct mode and disable FIFO
	DMA1_Stream6->FCR =0;

	//Enable DMA1 Stream 6
	DMA1_Stream6->CR |= DMA_CR_EN;

	//Enable UART2 Transmitter DMA
	USART2->CR3 |= UART_CR3_DMAT;

	//DMA Interrupt Enable in NVIC
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);


}
void uart2_rx_interrupt(void){
	/********Configure uart gpio*********/

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA-> MODER |= (1U<<5);
	GPIOA-> MODER &= ~(1U<<4);
 /*********PA2 ALternate function mode****/

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	GPIOA-> MODER &= ~(1U<<6);
	GPIOA-> MODER |= (1U<<7);

	/*********PA3 ALternate function mode****/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);



	RCC->APB1ENR |= UART2EN;

	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);


	USART2->CR1 = CR1_TE | CR1_RE;
	//Enable RXNE interrupt
		USART2->CR1 = CR1_RXNEIE;
		//Enable NVIC
		NVIC_EnableIRQ(USART2_IRQn);
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

char uart2_read(void)
{
	while(!(USART2->SR & SR_RXNE))
		{}
	return USART2->DR;
}
void uart2_write(int ch)
{
	while(!(USART2->SR & SR_TXE))
	{}

	USART2->DR = (ch & 0xFF);

}
