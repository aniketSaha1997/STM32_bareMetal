#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		16000
#define SYSTICK_ENABLE			(1U<<0)
#define SYSTICK_CLK_SRC			(1U<<2)
#define SYSTICK_COUNTFLG		(1U<<16)

void systickDelayms(int n)
{
	SysTick-> LOAD = SYSTICK_LOAD_VAL;
	SysTick->VAL = 0;
	SysTick->CTRL = SYSTICK_ENABLE | SYSTICK_CLK_SRC;

	for(int i=0;i<n;i++){
		while((SysTick->CTRL & SYSTICK_COUNTFLG)==0)
		{}
	}
	SysTick->CTRL = 0;
}
