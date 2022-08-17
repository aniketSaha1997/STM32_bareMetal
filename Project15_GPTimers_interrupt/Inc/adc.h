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
#endif /* ADC_H_ */
