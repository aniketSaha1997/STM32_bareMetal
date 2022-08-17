#include "stm32f4xx.h"

#define TIM2_ENABLE		(1U<<0)
#define CR1_CEN			(1U<<0)
#define DIER_UIE		(1U<<0)

void tim2_1Hz_init(void)
{
	//Enable clock to access tim2
	RCC->APB1ENR |= TIM2_ENABLE;
	//Set prescaler
	TIM2->PSC =1600 - 1; //16 000 000 / 1 600 = 10 000
	//Set ARR
	TIM2->ARR = 10000 - 1; // 10 000/ 10 000 = 1Hz
	//Clear counter
	TIM2->CNT = 0;
	//Enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim2_1Hz_interrupt_init(void)
{
	//Enable clock to access tim2
	RCC->APB1ENR |= TIM2_ENABLE;
	//Set prescaler
	TIM2->PSC =1600 - 1; //16 000 000 / 1 600 = 10 000
	//Set ARR
	TIM2->ARR = 10000 - 1; // 10 000/ 10 000 = 1Hz
	//Clear counter
	TIM2->CNT = 0;
	//Enable timer
	TIM2->CR1 = CR1_CEN;

	TIM2->DIER |= DIER_UIE;

	NVIC_EnableIRQ(TIM2_IRQn);
}
