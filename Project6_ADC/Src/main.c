#include <stdio.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"
#define GPIOAEN		(1U<<0)
#define GPIOA_5		(1U<<5)

#define LED_PIN		GPIOA_5


uint32_t sensor_val;
int main(void)
{


	 uart2_rxtx_init();
	 PA1_adc_init();
	 start_conversion();
	while(1)
	{
		start_conversion();
		sensor_val =adc_read();
		printf("Sensor value =  %d \n\r", (int)sensor_val);

	}
}


