/*
 * timer.h
 *
 *  Created on: 13 Aug 2022
 *      Author: aniket
 */

#ifndef TIMER_H_
#define TIMER_H_

void tim2_1Hz_init(void);
void tim2_PA5_output_compare(void);
void tim3_pa6_input_capture(void);
#define SR_UIF		(1U<<0)
#define SR_CC1IF	(1U<<0)
#endif /* TIMER_H_ */
