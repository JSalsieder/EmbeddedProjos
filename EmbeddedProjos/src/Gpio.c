/*
 * Gpio.c
 *
 *  Created on: Jan 26, 2017
 *      Author: salsiederja
 */

#include "Gpio.h"

void Gpio_setup(_gpio *g){
	 uint32_t* reg;
	 reg = g;
	 for(int i = 1; i <= 9; i++){
		 *(reg+i) = *(reg)+(i*4);
	 }
	 Gpio_enable(g);
 }

void Gpio_digitalWrite(_gpio *g, uint8_t pin, Speed Low_or_High){
	switch (Low_or_High){
	case Low:
		Gpio_writeLow(g, pin);
		break;
	case High:
		Gpio_writeHigh(g, pin);
		break;
	default:
		break;
	}
}

void Gpio_writeHigh(_gpio *g, uint8_t pin){
	*(g->ODR) |= (1<<pin);
 }

void Gpio_writeLow(_gpio *g, uint8_t pin){
	 *(g->ODR) &= ~(1<<pin);
 }

void Gpio_Pullup(_gpio *g, uint8_t pin){
	 *(g->OTYPER) &= ~(1<<pin);
	 *(g->PUPDR) &= ~(3<<(pin*2));
	 *(g->PUPDR) |= PullUp<<(pin*2);
 }

void Gpio_PullDown(_gpio *g, uint8_t pin){
	 *(g->OTYPER) &= ~(1<<pin);
	 *(g->PUPDR) &= ~(3<<(pin*2));
	 *(g->PUPDR) |= PullDown<<(pin*2);
 }

void Gpio_NoResistor(_gpio *g, uint8_t pin){
	 *(g->OTYPER) &= ~(1<<pin);
	 *(g->PUPDR) &= ~(3<<(pin*2));
	 *(g->PUPDR) |= None<<(pin*2);
 }

int Gpio_digitalRead(_gpio *g, uint8_t pin){
	int ret = 0;
	ret = *(g->IDR) &= (1<<pin);
	ret= ret>>pin;
	ret &= 1;
	return ret;
}

void Gpio_pinMode(_gpio *g, uint8_t pin, Mode mode){
	 *(g->MODER) &= ~(0b11 << pin*2);
	 switch(mode){
	 case Input:
		 *(g->MODER) |= (Input<<pin*2);
		 break;
	 case Output:
		 *(g->MODER) |= (Output<<pin*2);
		 break;
	 case AltFunct:
		 *(g->MODER) |= (AltFunct<<pin*2);
		 break;
	 case Analog:
		 *(g->MODER) |= (Analog<<pin*2);
		 break;

	 }
 }

void Gpio_AlternateFunction(_gpio *g, uint8_t pin, AltFunction AFx){
	 *(g->MODER) &= ~(3<<pin*2);
	 *(g->MODER) |= AltFunct<<(pin*2);
	 if(pin < 16 && pin > 7 ){
		 *(g->AFRH) &= ~(0xf<<((pin-8)*4));
		 *(g->AFRH) |= (AFx<<((pin-8)*4));
	 }else if(pin < 8){
		 *(g->AFRL) &= ~(0xf<<(pin*4));
		 *(g->AFRL) |= (AFx<<(pin*4));
	 }
 }

void Gpio_enable(_gpio *g){
	uint8_t RCC_bitField;
	uint32_t Port =g->MODER;
	switch(Port){
	case GPIOA: RCC_bitField = 0;	break;
	case GPIOB:	RCC_bitField = 1;	break;
	case GPIOC: RCC_bitField = 2;	break;
	case GPIOD:	RCC_bitField = 3; 	break;
	case GPIOE: RCC_bitField = 4;	break;
	case GPIOF: RCC_bitField = 5;	break;
	case GPIOG: RCC_bitField = 6;	break;
	case GPIOH: RCC_bitField = 7;	break;
	}
	*(RCC_AHB1ENR) |= (1<<RCC_bitField);
}

void Gpio_disable(_gpio *g){
	uint8_t RCC_bitField;
	uint32_t Port =g->MODER;
	switch(Port){
	case GPIOA: RCC_bitField = 0;	break;
	case GPIOB:	RCC_bitField = 1;	break;
	case GPIOC: RCC_bitField = 2;	break;
	case GPIOD:	RCC_bitField = 3; 	break;
	case GPIOE: RCC_bitField = 4;	break;
	case GPIOF: RCC_bitField = 5;	break;
	case GPIOG: RCC_bitField = 6;	break;
	case GPIOH: RCC_bitField = 7;	break;
	}
	*(RCC_AHB1ENR) &= ~(1<<RCC_bitField);
}
