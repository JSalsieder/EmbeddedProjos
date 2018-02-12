/*
 * DMX512_Universe.h
 *
 *  Created on: Feb 7, 2017
 *      Author: salsiederja
 */

#ifndef DMX512_UNIVERSE_H_
#define DMX512_UNIVERSE_H_


typedef struct {
	uint16_t address;
	uint8_t values[512];
} DMX512;



uint8_t DMX_getNext(DMX512*);
uint8_t DMX_get(DMX512*, uint16_t address);




#endif /* DMX512_UNIVERSE_H_ */
