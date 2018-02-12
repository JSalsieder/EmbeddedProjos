/*
 * uart1.h
 *
 *  Created on: Feb 12, 2017
 *      Author: salsiederja
 */

#ifndef UART1_H_
#define UART1_H_

#include "defines.h"
#include "gpio.h"




void init_usart1();


void usart1_write(uint8_t data);


#endif /* UART1_H_ */
