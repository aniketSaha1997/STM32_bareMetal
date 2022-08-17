/*
 * uart.h
 *
 *  Created on: 11 Aug 2022
 *      Author: aniket
 */
#include "stm32f4xx.h"
#include <stdint.h>

#ifndef UART_H_
#define UART_H_

void uart2_tx_init(void);
void uart2_rx_interrupt(void);
#define SR_RXNE		(1U<<5)
#endif /* UART_H_ */
