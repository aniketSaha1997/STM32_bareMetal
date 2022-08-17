/*
 * adc.h
 *
 *  Created on: 12 Aug 2022
 *      Author: aniket
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void PA1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);
void PA1_adc_interrupt_init(void);

#define EOC_FLAG_SR		(1U<<1)

#endif /* ADC_H_ */
