/*
 * encoder.c
 *
 *  Created on: Feb 4, 2017
 *      Author: salsiederja
 */


#include "encoder.h"
#ifndef ISER1
#define ISER1 (volatile uint32_t*) 0xE000E104
#define ICER1 (volatile uint32_t*) 0xE000E184
#define ISPR1 (volatile uint32_t*) 0xE000E204
#define ICPR1 (volatile uint32_t*) 0xE000E284
#endif

#ifndef ISER0
#define ISER0 (volatile uint32_t*) 0xE000E100
#define ICER0 (volatile uint32_t*) 0xE000E180
#define ISPR0 (volatile uint32_t*) 0xE000E200
#define ICPR0 (volatile uint32_t*) 0xE000E280
#endif

#define NVIC_IPR1 (volatile uint32_t*) 0xE000E404

#define EXTI0_NVIC 6
#define EXTI1_NVIC 7
#define EXTI15thru10_NVIC 8


typedef struct{
	uint32_t* IMR;
	uint32_t* EMR;
	uint32_t* RTSR;
	uint32_t* FTSR;
	uint32_t* SWIER;
	uint32_t* PR;
}_Exti;

typedef struct{
	uint32_t* MEMRM;
	uint32_t* PMC;
	uint32_t* EXTICR1;
	uint32_t* EXTICR2;
	uint32_t* EXTICR3;
	uint32_t* EXTICR4;
	uint32_t* CMPCR;
}_SysConfig;

static Fptr ISR;
static _Exti EXTI = {(uint32_t*)0x40013c00, (uint32_t*)0x40013c04, (uint32_t*)0x40013c08, (uint32_t*)0x40013c0c, (uint32_t*)0x40013c10, (uint32_t*)0x40013c14};
static _SysConfig SYSCONFIG = {(uint32_t*)0x40013800, (uint32_t*)0x40013804, (uint32_t*)0x40013808, (uint32_t*)0x4001380c, (uint32_t*)0x40013810, (uint32_t*)0x40013814, (uint32_t*)0x40013820};
static volatile int ENCODER_VAL;
static _gpio GpioA ={GPIOA};

void Encoder_init(void){
	Gpio_setup(&GpioA);
//enable the gpio ports for the encoder by putting each in input mode with a pullup resistor
	Gpio_Pullup(&GpioA, 0);
	Gpio_pinMode(&GpioA, 0, Input);
	Gpio_Pullup(&GpioA, 1);
	Gpio_pinMode(&GpioA, 1, Input);
	Gpio_Pullup(&GpioA, 12);
	Gpio_pinMode(&GpioA, 12, Input);
//Configure the SystemConfiguration register to acknowledge Interupts from port A pins 0, 1 and 12
	*(SYSCONFIG.EXTICR1) &= ~(7<<0 | 7<<4);
	*(SYSCONFIG.EXTICR4) &= ~(7<<0);
//Configure the EXTI registers to use both falling and rising edge detection
	*(EXTI.FTSR) |= ((1 << 0 )|( 1 << 1 )|( 1 << 12 ));
	*(EXTI.RTSR) |= ((1 << 0 )|( 1 << 1 )|( 1 << 12 ));
//NVIC LINE POSITIONS 6, 7, 40
	*(ISER0) |= (1<<EXTI0_NVIC | 1<<EXTI1_NVIC);
	*(ISER1) |= (1<<EXTI15thru10_NVIC);
	(*NVIC_IPR1) |= (3 << 16+3) | (3 << 24+3);  // lower the interrupt priority to level 3 So DMA will take precedence;
	ENCODER_VAL = Encoder_get_value();
}

int Encoder_get_value(){
	int x = (Gpio_digitalRead(&GpioA, 1) << 1 | Gpio_digitalRead(&GpioA, 0));
	if(x == 3){ return 2; }
	if(x == 2){ return 3; }
	return x;
}

void Encoder_Interrupts(Fptr p){
	ISR = p;
	(*EXTI.IMR) |= 1 << 0 | 1 << 1;  //ENABLE INTERRUPT MASK ON GPIO PX.0 and PX.1
	(*EXTI.RTSR) |= 1 << 0 | 1 << 1; //RISING EDGE TRIGGERED ON GPIO PX.0 and PX.1
	(*EXTI.FTSR) |= 1 << 0 | 1 << 1; //FALLING EDGE TRIGGERED ON GPIO PX.0 and PX.1

	(*SYSCONFIG.EXTICR1) &=  0xFFFFFF00; // set the EXTI PORT to Port A
	(*ISER0) |= (1 << 6 | 1 << 7);
}

void Encoder_noInterrupts(){
	//(*EXTI.IMR) &= ~(1 << 0 | 1 << 1); //DISABLE INTERRUPT MASK ON GPIO PX.0 and PX.1
	(*ICPR0) |= (1 << 6 | 1 << 7);
	(*ICER0) |= (1 << 6 | 1 << 7);
}

void EXTI0_IRQHandler(){
	ISR();
	(*EXTI.PR) |= 0b11;
}

void EXTI1_IRQHandler(){
	ISR();
	(*EXTI.PR) |= 0b11;

}

int Encoder_get_direction(){
	int temp = 0;
	temp = (ENCODER_VAL << 2) | Encoder_get_value();
	ENCODER_VAL = (temp & 0x3);
	return (temp & 0b0011) - (temp & 0b1100);
}

