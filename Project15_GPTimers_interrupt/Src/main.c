#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5)

#define LED_PIN		GPIOA_5


static void tim2_callback(void);
int main(void)
{
	RCC->AHB1ENR |= GPIOAEN	;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	 uart2_rxtx_init();
	// tim2_1Hz_init();
	 tim2_1Hz_interrupt_init();

	while(1)
	{



	}
}

static void tim2_callback(void)
{
	printf("Second Passed =  \n\r");
	GPIOA->ODR ^= LED_PIN;

}
void ITM2_IRQHandler(void)
{
	TIM2->SR &= ~SR_UIF;

		tim2_callback();


}
