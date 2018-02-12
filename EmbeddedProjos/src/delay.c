/*
 * delay.c
 *
 *  Created on: Dec 31, 2016
 *      Author: salsiederja
 */

#include "delay.h"

#ifndef DEFINES_H_
#include "defines.h"
#endif

#define STK_CTRL (volatile uint32_t*) 0xE000E010
#define STK_LOAD (volatile uint32_t*) 0xE000E014
#define STK_VAL (volatile uint32_t*) 0xE000E018
#define STK_ENABLE_FLAG 0
#define STK_CLKSOURCE_FLAG 2
#define STK_CNTFLAG_FLAG 16

/**
 * delay for a number of miliseconds
 *
 * @param ms = milliseconds to delay
 */
void delay(int ms){
	//make sure counter is off
	*(STK_CTRL) &= ~(1<< STK_ENABLE_FLAG);
	//#ms times
	for( uint32_t i=0; i < ms; i++){
		// load 16000 into STK_LOAD
		*(STK_LOAD) = 16000;  // 1ms
		// turn on counter
		*(STK_CTRL) |= ((1 << STK_ENABLE_FLAG) | (1 << STK_CLKSOURCE_FLAG));
		// poll for flag == 1
		while((*(STK_CTRL) & (1<<STK_CNTFLAG_FLAG)) != (1<<STK_CNTFLAG_FLAG)){}
		// turn off counter
		*(STK_CTRL) &= ~(1<<STK_ENABLE_FLAG);
	}
}


