#include "stm32f4xx.h"

#define GPIOAEN 	(1U<<0)
#define GPIOCEN 	(1U<<2)


#define PIN5		(1U<<5)
#define PIN13		(1U<<13)

#define BTN			PIN13
#define LED_PIN		PIN5

int main(void)
{
	RCC ->AHB1ENR |= GPIOCEN;
	RCC ->AHB1ENR |= GPIOAEN;


	GPIOA-> MODER |= (1U<<10);
	GPIOA-> MODER &= ~(1U<<11);

	GPIOA-> MODER &= ~(1U<<26);
	GPIOA-> MODER &= ~(1U<<27);


	while(1)
	{

		if(GPIOA-> IDR & BTN){

		GPIOA-> BSRR =LED_PIN;

		}
		else
		{
		GPIOA-> BSRR =(1U<<21);

		}

	}
}
