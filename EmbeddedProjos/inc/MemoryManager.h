/*
 * MemoryManager.h
 *
 *  Created on: Feb 7, 2017
 *      Author: salsiederja
 *
 *      Purpose of this file:
 *      Provide a LongTerm-Memory Storage Manager both for storing and recalling Ques for the DMX board
 *
 *      channel is used for saving data to EEPROM as efficiently as possible.
 *      The idea will be to save a file in the following manner:
 *      [ non-0 channel number (16bits) ][ value of previous channel (8bits) ]...[next non-0 channel][next value]... [\0 (16bit)] //end of file
 *      so the file in memory should look something like this:
 *      [1][56] [3][25] [4][25] [6][200] [100][50] [\0]
 *      the idea is that when reading the file back into a buffer(array) any values that are not expressly given should be set to 0
 *      in the case of the previous example channels 2,5,7 thru 99, and 101 thru 512 should not be changed from an initial value of 0
 *      in this way the Maximum size for a saved QUE in EEPROM is 1538 Bytes occurring when no channel has a value of 0 and the Minimum file
 *      size will be 2 Bytes where every channel is at 0 and the only character in the file is a 16bit Null terminator.
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include <stdlib.h>
#include "DMX512_Universe.h"

typedef struct {
	uint16_t address;
	uint8_t value;
}channel;



//I need to create a pointer table in EEPROM to store the pointer to all the cues
//  what the pointer table must look like all ptrX are words
//0x(0)000 [ptr to last location Written to][ptr1] [ptr2] [ptr3] [] [] [] [] [] [] [] [] [] [] [] [ptr15] ... [ptr105]
//address of table							 first ptrX														  last ptrX maximum number of QUES


//Place the next QUE in EEPROM
void EEPROM_saveQUE(DMX512*, uint32_t CUE_ID);

//places the Universe in the heap and returns the address for the Universe
DMX512* EEPROM_loadQUE(uint32_t CUE_ID);

//INTERNAL METHODS
//LOG_STATE() SAVES THE STATES OF ALL THE GPIO_s BEFORE ENTERING A LOAD OR SAVE;
//THEN SETS THEM TO BE USED BY THE EEPROM AS GPIO's
static void EEPROM_LOG_STATE(void);
//RECALL_STATE() RETURNS THE STATE OF THE GPIO PINS TO BE AS THEY WERE WHEN LOG_STATE() WAS CALLED
static void EEPROM_RECALL_STATE(void);





#endif /* MEMORYMANAGER_H_ */
