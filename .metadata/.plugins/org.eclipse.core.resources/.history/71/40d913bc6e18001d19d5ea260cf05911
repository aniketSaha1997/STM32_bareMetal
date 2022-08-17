// What to do? LIGHT LED
// Port : A
//PIN : 5

#define PERIPH_BASE				(0x40000000UL)
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000U)
#define GPIOA_BASE 				(AHB1PERIPH_OFFSET + GPIOA_OFFSET)

#define RCC_OFFSET				(0x00003800UL)
#define RCC_BASE 				(AHB1PERIPH_OFFSET + RCC_OFFSET)

#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET 			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))


#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN					(1U<<0)  // 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5					(1U<<5)
#define LED_PIN 				PIN5




int main(void)
{
	//ENABLE CLOCK ACCESS TO GPIOA
	//SET PA5 AS OUTPUT PIN
	RCC_AHB1EN_R |= GPIOAEN;

	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &= ~(1U<<11);

	while(1)
	{
		//SET PA5 HIGH
		GPIOA_OD_R |= LED_PIN;

	}
}
