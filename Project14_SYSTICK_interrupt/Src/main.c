#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5)

#define LED_PIN		GPIOA_5


static void systick_callback(void);
int main(void)
{
	RCC->AHB1ENR |= GPIOAEN	;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	 uart2_rxtx_init();
	 SysTick_1hz_interrupt();
	while(1)
	{

		//sensor_val =adc_read();
		//systickDelayms(1000);

	}
}
static void systick_callback(void)
{

			printf("Second Passed =  \n\r");
			GPIOA->ODR ^= LED_PIN;
}

void SysTick_Handler(void)
{
	systick_callback();
}
