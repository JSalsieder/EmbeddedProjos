/*
 * DS75176B.h
 *
 *  Created on: Feb 7, 2017
 *      Author: salsiederja
 *      creates a DS75176B structure to interface with the Transceiver IC of the same code
 */

#ifndef DS75176B_H_
#define DS75176B_H_

#include <stdlib.h>

#include "inttypes.h"
#include "Gpio.h"
#include "error.h"


typedef struct{
	_gpio *port;
	uint8_t pin;
} pinMap;


typedef struct {
	pinMap RO;
	pinMap _RE;
	pinMap DE;
	pinMap DI;
}DS75176B;


DS75176B* Transciever_init();
void Transciever_Output(DS75176B* chip);
void Transciever_Input(DS75176B* chip);
void Transciever_HiZ(DS75176B* chip);



#endif /* DS75176B_H_ */
