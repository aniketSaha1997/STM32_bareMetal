#include "exti.h"
#include "stm32f4xx.h"

#define GPIOCEN		(1U<<2)
#define SYSCFGEN		(1U<<14)
void pc13_exti_init(void){

	//Disable global interrupts
	__disable_irq();

	//Enable clock access for GPIOC
	RCC->AHB1ENR |= GPIOCEN;

	//Enable clock access for SYSCFG
	RCC->APB2ENR |= SYSCFGEN;
	//Select PORTC for EXTI13
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	SYSCFG->EXTICR[3] |= (1U<<5);
	//Unmask EXTI13
	EXTI->IMR |= (1U<<13);
	//Select falling edge
	EXTI->FTSR |= (1U<<13);
	//Enable EXTI13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	//Enable global interrupts
	__enable_irq();
}
