/*
 * AT28C256.h
 *
 *  Created on: Feb 7, 2017
 *      Author: salsiederja
 */

#ifndef AT28C256_H_
#define AT28C256_H_

#define ROM_MAX_ADDRESS 0x7FFF

#include <stdio.h>
#include <stdlib.h>
#include "inttypes.h"
#include "uart_driver.h"
#include "error.h"
#include "Gpio.h"


typedef struct{
	_gpio *port;
	uint8_t pin;
} SpinMap;

typedef struct{
	SpinMap OE; SpinMap CE; SpinMap WE;
	SpinMap A0;	SpinMap A1;	SpinMap A2;	SpinMap A3; SpinMap A4; SpinMap A5; SpinMap A6; SpinMap A7;
	SpinMap A8;	SpinMap A9;	SpinMap A10; SpinMap A11; SpinMap A12; SpinMap A13; SpinMap A14;

	SpinMap IO0; SpinMap IO1; SpinMap IO2; SpinMap IO3;	SpinMap IO4; SpinMap IO5; SpinMap IO6; SpinMap IO7;
} SEeprom_pins;

typedef enum {LOW, HIGH} g_eState;

typedef enum {PA, PB, PC, PD, PH} g_ePorts;

SEeprom_pins* ROM_init();

void ROM_write(SEeprom_pins* rom, const uint32_t dataAddress, const uint8_t dataByte);

uint8_t ROM_read(SEeprom_pins* rom, const uint32_t dataAddress);







#endif /* AT28C256_H_ */
