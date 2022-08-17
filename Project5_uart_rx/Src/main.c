#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"

int main(void)
{
	 uart2_tx_init();


	while(1)
	{

		printf("Hello From Stm32F4..\n\r");

	}
}


