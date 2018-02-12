/*
 * DMA.h
 *
 *  Created on: Feb 14, 2017
 *      Author: salsiederja
 */

#ifndef DMA_H_
#define DMA_H_

#include "defines.h"
#include "error.h"
#include <stdlib.h>
#include <inttypes.h>


void DMA_init(uint8_t* start_address, uint32_t numberOfBytes);

void DMA2_Stream7_IRQHandler() __attribute__ ((isr));

#endif /* DMA_H_ */
