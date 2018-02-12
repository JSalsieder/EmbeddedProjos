/*
 * Timers.h
 *
 *  Created on: Jan 25, 2017
 *      Author: salsiederja
 */

#ifndef TIMERS_H_
#define TIMERS_H_
#include "inttypes.h"
#include "defines.h"

typedef struct {
	uint32_t* CR1;
	uint32_t* CR2;
	uint32_t* SMCR;
	uint32_t* DIER;
	uint32_t* SR;
	uint32_t* EGR;
	uint32_t* CCMR1_IO;
	uint32_t* CCMR2_IO;
	uint32_t* CCER;
	uint32_t* CNT;
	uint32_t* PSC;
	uint32_t* ARR;
	uint32_t* reserved;
	uint32_t* CCR1;
	uint32_t* CCR2;
	uint32_t* CCR3;
	uint32_t* CCR4;
	uint32_t* DCR;
	uint32_t* DMAR;

} _timerGeneralPurpose;

typedef void(*ISR)();

void Timer_setup(_timerGeneralPurpose*);
void Timer_enable(_timerGeneralPurpose*);
void Timer_disable(_timerGeneralPurpose*);
void Timer_setPrescalar(_timerGeneralPurpose*, uint16_t);
void Timer_setAutoReload(_timerGeneralPurpose*, uint16_t);
void Timer_setCCValue(_timerGeneralPurpose*, uint16_t);
void Timer_start(_timerGeneralPurpose*);
void Timer_stop(_timerGeneralPurpose*);
void Timer_outputCompareMode(_timerGeneralPurpose*);
uint32_t Timer_getCNT(_timerGeneralPurpose*);
void Timer_tone(_timerGeneralPurpose*, uint16_t);
void Timer_ttone(_timerGeneralPurpose*, uint16_t, uint16_t);
void Timer_noTone(_timerGeneralPurpose*);
void Timer_enableInterrupt(_timerGeneralPurpose*, ISR);
void Timer_dissableInterrupt(_timerGeneralPurpose*);

#endif /* TIMERS_H_ */
