#include "stm32f4xx.h"
#include "adc.h"
#define ADC1EN			(1U<<8)
#define	GPIOAEN			(1U<<0)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1	 0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define CR2_CONT		(1U<<1)

#define CR1_EOCIE		(1U<<5)

void PA1_adc_init(void)
{
	/*Enable Clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*SET MODE TO PA1*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	RCC->APB2ENR |=ADC1EN;

	/*CONFIG ADC PARAMETERS*/
	/*CONFIG SEQ START*/
	ADC1->SQR3 = ADC_CH1;

	/*CONVERSION SEQ LENGTH*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	/*ENABLE ADC MODULE*/
	ADC1->CR2 |= CR2_ADON;

}

void PA1_adc_interrupt_init(void)
{
	/*Enable Clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*SET MODE TO PA1*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	RCC->APB2ENR |=ADC1EN;

	/*CONFIG ADC PARAMETERS*/
	/*CONFIG SEQ START*/
	ADC1->SQR3 = ADC_CH1;

	/*CONVERSION SEQ LENGTH*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	ADC1->CR1 |= CR1_EOCIE;

	NVIC_EnableIRQ(ADC_IRQn);
	/*ENABLE ADC MODULE*/
	ADC1->CR2 |= CR2_ADON;

}

void start_conversion(void)
{
	ADC1->CR2 |= CR2_CONT;
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	while(!(ADC1->SR & EOC_FLAG_SR))
	{}
	return (ADC1->DR);
}
