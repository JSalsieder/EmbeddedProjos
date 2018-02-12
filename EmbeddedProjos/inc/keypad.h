/*
 * keypad.h
 *
 *  Created on: Dec 23, 2016
 *      Author: salsiederja
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "defines.h"


/**
 * initilizes the GPIO's for the keypad
 */
void kpad_begin();

/**
 * Reads the Keypad once and returns the value
 * if no input returns 0xF
 */
int kpad_read();

/**
 * polling method, returns the first Non-zero keypress
 */
int kpad_poll();


#endif /* KEYPAD_H_ */
