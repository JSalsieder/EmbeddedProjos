/*
 * Gpio.h
 *
 *  Created on: Jan 25, 2017
 *      Author: salsiederja
 */

#ifndef GPIO_H_
#define GPIO_H_
#include "inttypes.h"
#include "defines.h"

typedef struct {
	uint32_t* MODER;
	uint32_t* OTYPER;
	uint32_t* OSPEEDR;
	uint32_t* PUPDR;
	uint32_t* IDR;
	uint32_t* ODR;
	uint32_t* BSRR;
	uint32_t* LCKR;
	uint32_t* AFRL;
	uint32_t* AFRH;

} _gpio;
//typedef enum{Low, High} value;
typedef enum{Input, Output, AltFunct, Analog} Mode;
typedef enum{Low, Medium, Fast, High} Speed;
typedef enum{None, PullUp, PullDown} Resistor;
typedef enum{AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8, AF9,
			AF10, AF11, AF12, AF13, AF14, AF15} AltFunction;

//Gpio_setup must be called before any other function or the behavior is undefined
void Gpio_setup(_gpio*);
void Gpio_digitalWrite(_gpio*, uint8_t, Speed);
void Gpio_writeHigh(_gpio*, uint8_t);
void Gpio_writeLow(_gpio*, uint8_t);
void Gpio_Pullup(_gpio*, uint8_t);
void Gpio_PullDown(_gpio*, uint8_t);
void Gpio_NoResistor(_gpio*, uint8_t);
void Gpio_AlternateFunction(_gpio*, uint8_t, AltFunction);
void Gpio_enable(_gpio*);
void Gpio_disable(_gpio*);
void Gpio_pinMode(_gpio*, uint8_t, Mode);
int Gpio_digitalRead(_gpio *g, uint8_t pin);

#endif /* GPIO_H_ */
