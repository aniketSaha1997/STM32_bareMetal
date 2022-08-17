// What to do? LIGHT LED
// Port : A
//PIN : 5
#include <stdint.h>
#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000U)
#define GPIOA_BASE 				(AHB1PERIPH_OFFSET + GPIOA_OFFSET)

#define RCC_OFFSET				(0x00003800UL)
#define RCC_BASE 				(AHB1PERIPH_OFFSET + RCC_OFFSET)


#define GPIOAEN					(1U<<0)  // 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5					(1U<<5)
#define LED_PIN 				PIN5

#define __IO volatile


typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
} GPIO_TypeDef;


typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
} RCC_TypeDef;


#define RCC				((RCC_TypeDef*) RCC_BASE)
#define GPIOA			((GPIO_TypeDef*) GPIOA_BASE)

int main(void)
{
	//ENABLE CLOCK ACCESS TO GPIOA
	//SET PA5 AS OUTPUT PIN


	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);


	while(1)
	{
		//SET PA5 HIGH
		GPIOA->ODR |= LED_PIN;

	}
}
