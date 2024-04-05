/*
 * timer.c
 *
 *  Created on: Apr 6, 2024
 *      Author: shraddha
 */

#include "timer.h"

volatile uint8_t gcnt =0;
void TimerInit(uint32_t ms) {
	// enable timer clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	// set prescalar
	TIM7->PSC = TIM_PR-1;
	//-----------------------------------------------
	// set number of clocks to count
		uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
		TIM7->ARR = cnt - 1;
		// start count from 0
		TIM7->CNT = 0;
		//---//enable  INTERRUPT bit  IN TIMER
		TIM7->DIER |= BV(0);
		//----enable interrrupt in nvic
		NVIC_EnableIRQ(TIM7_IRQn);
		// start timer counter
		TIM7->CR1 |= TIM_CR1_CEN;
}



void TIM7_IRQHandler (void){
	// CHECK IF INTERRUPT OCCURED
	if ((TIM7->SR & TIM_SR_UIF)==1){
		//clear the aknowledg interrupt
		TIM7->SR &= ~TIM_SR_UIF;
          gcnt ++;
	}

	}
	 // WRITE INTERRUPUT HANDLER IF NOT OCCURED








