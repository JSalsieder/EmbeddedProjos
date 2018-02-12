/*
 * encoder.h
 *
 *  Created on: Feb 4, 2017
 *      Author: salsiederja
 */

#ifndef ENCODER_H_
#define ENCODER_H_
#include "inttypes.h"
#include "gpio.h"
typedef struct {
	uint8_t value;
} Encoder;

typedef void(*Fptr)();

//prototypes
void Encoder_init();

//function pointer to ISR
void Encoder_Interrupts(Fptr);

void Encoder_noInterrupts();

void EXTI0_IRQHandler() __attribute__ ((isr));

void EXTI1_IRQHandler() __attribute__ ((isr));

//TODO:
void EXTI15_10_IRQHandler() __attribute__ ((isr));

int Encoder_get_direction();

int Encoder_get_value();

#endif /* ENCODER_H_ */

