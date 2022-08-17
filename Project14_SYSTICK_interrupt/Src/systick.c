#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL		16000
#define SYSTICK_ENABLE			(1U<<0)
#define SYSTICK_CLK_SRC			(1U<<2)
#define SYSTICK_COUNTFLG		(1U<<16)

#define ONE_SEC_LOAD			16000000
#define CR_TICKINT				(1U<<1)
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

void SysTick_1hz_interrupt(void)
{
	SysTick-> LOAD = ONE_SEC_LOAD -1;
	SysTick->VAL = 0;
	SysTick->CTRL = SYSTICK_ENABLE | SYSTICK_CLK_SRC |CR_TICKINT;
}
