/*
 * DS75176B.c
 *
 *  Created on: Feb 12, 2017
 *      Author: salsiederja
 */

#include "DS75176B.h"
enum {A, B};
static _gpio port[2] = {{GPIOA}, {GPIOB}};

DS75176B* Transciever_init(){
	DS75176B* tempChip = malloc(sizeof(DS75176B));
	if (tempChip == 0){
		EXCEPTION(FATAL_ERROR, "FAILED TO ALLOCATE MEMORY: DS75176B.c : 14");
		return 0;
	}
	pinMap temp = {(_gpio*)GPIOB, 7};

	//assign the pinMaps of the structure to the proper values
	tempChip->RO = temp;
	temp.pin = 6;
	tempChip->DI = temp;
	temp.pin = 5;
	temp.port = (_gpio*)GPIOA;
	tempChip->DE = temp;
	temp.pin = 4;
	tempChip->_RE = temp;
	Gpio_setup(&port[A]);
	Gpio_setup(&port[B]);

	return tempChip;
}

void Transciever_Output(DS75176B* chip){

	Gpio_Pullup(&port[A], chip->DE.pin);
	Gpio_Pullup(&port[A], chip->_RE.pin);
	Gpio_AlternateFunction(&port[B], chip->DI.pin, AF7);
}

//TODO:
void Transciever_Input(DS75176B* chip){}

//TODO:
void Transciever_HiZ(DS75176B* chip){}
