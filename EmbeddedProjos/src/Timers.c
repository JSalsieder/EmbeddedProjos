/*
 * Timers.c
 *
 *  Created on: Jan 25, 2017
 *      Author: salsiederja
 */

#include "Timers.h"




void Timer_setup(_timerGeneralPurpose *t){
	 uint32_t* reg;
	 reg = t;
	 for(int i = 1; i <= 18; i++){
		 *(reg+i) = *(reg)+(i*4);
	 }
	 Timer_enable(t);
 }

void Timer_enable(_timerGeneralPurpose *t){
	uint32_t address = t->CR1;
	switch(address){
	case TIM2: *(RCC_APB1ENR) |= (1<<0); break;
	case TIM3: *(RCC_APB1ENR) |= (1<<1); break;
	case TIM4: *(RCC_APB1ENR) |= (1<<2); break;
	case TIM5: *(RCC_APB1ENR) |= (1<<3); break;
	}

}

void Timer_disable(_timerGeneralPurpose *t){
	uint32_t address = t;
	switch(address){
	case TIM2: *(RCC_APB1ENR) &= ~(1<<0); break;
	case TIM3: *(RCC_APB1ENR) &= ~(1<<1); break;
	case TIM4: *(RCC_APB1ENR) &= ~(1<<2); break;
	case TIM5: *(RCC_APB1ENR) &= ~(1<<3); break;
	}
}

void Timer_setPrescalar(_timerGeneralPurpose *t, uint16_t prescalar){
	*(t->PSC) &= 0xFFFF0000;
	*(t->PSC) = prescalar;
}

void Timer_setAutoReload(_timerGeneralPurpose *t, uint16_t reload){
	*(t->ARR) &= 0xFFFF0000;
	*(t->ARR) |= reload;
}

void Timer_setCCValue(_timerGeneralPurpose* t, uint16_t value){
	*(t->CCR1) &= 0xFFFF0000;
	*(t->CCR1) |= value;
}

void Timer_start(_timerGeneralPurpose *t){
	*(t->CR1) |= 1;
}

void Timer_stop(_timerGeneralPurpose *t){
	*(t->CR1) &= ~1;
}

void Timer_outputCompareMode(_timerGeneralPurpose *t){
	*(t->CCMR1_IO) |= (0b111 << 4); // output = 1 when cnt < CCR1
	*(t->CCMR1_IO) &= ~(0b1 << 3); // New CCR values take immediate effect
	*(t->CCER) |= 1; //enable OutputCapture as signal on pin
	*(t->CR1) |= 1; //enable CaptureCompare;
	//??
	*(t->EGR) |= 0b11;
}

uint32_t Timer_getCNT(_timerGeneralPurpose* t){
	return *(t->CNT);
}


void Timer_tone(_timerGeneralPurpose* t, uint16_t frequency){
	Timer_outputCompareMode(t);
	Timer_setPrescalar(t, 0x80);
	uint16_t arr = 1/((double)frequency*(double)(0.000005));
	Timer_setAutoReload(t, arr);
	Timer_setCCValue(t, arr/2);
	Timer_start(t);
}

void Timer_ttone(_timerGeneralPurpose* t, uint16_t frequency, uint16_t millis){
	Timer_tone(t, frequency);
	delay(millis);
	Timer_noTone(t);
}

void Timer_noTone(_timerGeneralPurpose* t){
	Timer_stop(t);
}


































