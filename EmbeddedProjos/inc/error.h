/*
 * error.h
 *
 *  Created on: Feb 11, 2017
 *      Author: salsiederja
 */

#ifndef ERROR_H_
#define ERROR_H_
#include "inttypes.h"

enum eErrorTypes {FATAL_ERROR, ERROR, WARNING};

typedef char ErrorLog;

ErrorLog* EXCEPTION(int, char[]);

uint32_t getProgramLine() __attribute__ ((naked));

#endif /* ERROR_H_ */
