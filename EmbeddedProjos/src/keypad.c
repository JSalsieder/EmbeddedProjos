/*
 * keypad.c
 *
 *  Created on: Dec 23, 2016
 *      Author: salsiederja
 */

#include "keypad.h"

/*
 -------------------------
 KEYPAD GPIO'S

 ROW1	PC4
 ROW2	PC5
 ROW3	PC6
 ROW4	PC7

 COL1 	PC0
 COL2	PC1
 COL3	PC2
 COL4	PC3
 -------------------------
 */

void kpad_begin() {
	// set RCC clock for GPIOC
	*(RCC_AHB1ENR ) |= (1 << GPIOCEN_BF);

	// set GPIO pins as inputs with PullDown resistors
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_0_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_1_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_2_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_3_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_4_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_5_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_6_BF );
	*(GPIOC_MODER ) |= (GPIO_INPUT << MODER_7_BF );

	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_0_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_1_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_2_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_3_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_4_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_5_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_6_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_7_BF );

}

/*
 * scans through the
 */
static int row_scan() {
	int regValue;
	int returnValue;
	//read the values of the input data register for  pins [7..4]
	regValue = (*(GPIOC_IDR ) & 0xf0) >> 4;
	//return the row of the bottom most active switch
	// ie if both 4 and 7 are pressed  row 3 will be returned as it correlates
	// to the row with 7
	if (regValue & 0x1) {
		returnValue = 1;
	} else if (regValue & 0x2) {
		returnValue = 2;
	} else if (regValue & 0x4) {
		returnValue = 3;
	} else if (regValue & 0x8) {
		returnValue = 4;
	} else {
		returnValue = 0;
	}
	//return the row number
	return returnValue;
}

/*
 * given the input of the grid position returns the
 * integer of the keys value
 * ie. key#4 has a value of A
 * so if a 4 is entered the value 0xA is returned
 * # key returns 0xf, * key returns 0xe
 * if no key is pressed -1 is returned
 */
static int map(int keyNum) {
	int mappedVal;
	switch (keyNum) {
	case 1:
		mappedVal = 1;
		break;
	case 2:
		mappedVal = 2;
		break;
	case 3:
		mappedVal = 3;
		break;
	case 4:
		mappedVal = 0xA;
		break;
	case 5:
		mappedVal = 4;
		break;
	case 6:
		mappedVal = 5;
		break;
	case 7:
		mappedVal = 6;
		break;
	case 8:
		mappedVal = 0xB;
		break;
	case 9:
		mappedVal = 7;
		break;
	case 10:
		mappedVal = 8;
		break;
	case 11:
		mappedVal = 9;
		break;
	case 12:
		mappedVal = 0xC;
		break;
	case 13:
		mappedVal = 0xE;
		break;
	case 14:
		mappedVal = 0;
		break;
	case 15:
		mappedVal = 0xF;
		break;
	case 16:
		mappedVal = 0xD;
		break;
	default:
		mappedVal = -1;
	}
	return mappedVal;
}

int kpad_read() {
	//scan each row and return the first read value
	int readValue;
	// pull column 1 high
	*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_0_BF );
	*(GPIOC_MODER ) &= ~(0x3 << MODER_0_BF );
	*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_0_BF );
	*(GPIOC_BSRR ) |= (1 << BSRR_S_0_BF );
	//scan through the rows to find if one is pressed
	readValue = 4 * (row_scan() - 1) + 1;
//	if(readValue < 0){return 0;}
	// pull column 1 low again
	*(GPIOC_BSRR ) |= (1 << BSRR_R_0_BF );
	*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_0_BF );
	*(GPIOC_MODER ) &= ~(0x3 << MODER_0_BF );
	*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_0_BF );
	*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_0_BF );

	if (readValue < 0) {
		// pull column 2 high
		*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_1_BF );
		*(GPIOC_MODER ) &= ~(0x3 << MODER_1_BF );
		*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_1_BF );
		*(GPIOC_BSRR ) |= (1 << BSRR_S_1_BF );
		//scan through the rows to find if one is pressed
		readValue = 4 * (row_scan() - 1) + 2;
		//	if(readValue < 0){return 0;}
		// pull column 2 low again
		*(GPIOC_BSRR ) |= (1 << BSRR_R_1_BF );
		*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_1_BF );
		*(GPIOC_MODER ) &= ~(0x3 << MODER_1_BF );
		*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_1_BF );
		*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_1_BF );
	}

	if (readValue < 0) {
		// pull column 3 high
		*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_2_BF );
		*(GPIOC_MODER ) &= ~(0x3 << MODER_2_BF );
		*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_2_BF );
		*(GPIOC_BSRR ) |= (1 << BSRR_S_2_BF );
		//scan through the rows to find if one is pressed
		readValue = 4 * (row_scan() - 1) + 3;
		//if(readValue < 0){return 0;}
		// pull column 3 low again
		*(GPIOC_BSRR ) |= (1 << BSRR_R_2_BF );
		*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_2_BF );
		*(GPIOC_MODER ) &= ~(0x3 << MODER_2_BF );
		*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_2_BF );
		*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_2_BF );
	}

	if (readValue < 0) {
		// pull column 4 high
		*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_3_BF );
		*(GPIOC_MODER ) &= ~(0x3 << MODER_3_BF );
		*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_3_BF );
		*(GPIOC_BSRR ) |= (1 << BSRR_S_3_BF );
		//scan through the rows to find if one is pressed
		readValue = 4 * (row_scan() - 1) + 4;
		//if(readValue < 0){return 0;}
		// pull column 4 low again
		*(GPIOC_BSRR ) |= (1 << BSRR_R_3_BF );
		*(GPIOC_PUPDR ) &= ~(0x3 << PUPDR_3_BF );
		*(GPIOC_MODER ) &= ~(0x3 << MODER_3_BF );
		*(GPIOC_MODER ) |= (GPIO_OUTPUT << MODER_3_BF );
		*(GPIOC_PUPDR ) |= (GPIO_PULLDOWN << PUPDR_3_BF );
	}

	if (readValue < 0) {
		readValue = 0;
	}
	return map(readValue);

}


int kpad_poll() {
	int key;
	do {
		key = kpad_read();
	} while (key == -1);
	return key;
}

