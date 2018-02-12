/*
 * error.c
 *
 *  Created on: Feb 11, 2017
 *      Author: salsiederja
 */
#include "error.h"



ErrorLog* EXCEPTION(int E, char* msg){
	switch (E){
	case FATAL_ERROR:
		printf("A FATAL ERROR HAS OCCURED!: *SYSTEM RESET* - CAUSED BY :%s  LINE: %p", msg, getProgramLine());
		for(;;){asm("b Reset_Handler");}
		break;
	case ERROR:	return "ERROR: ";		break;
	case WARNING: return "WARNING: ";	break;
	default: return 0;
	}
}

uint32_t getProgramLine(){
	register uint32_t* linkReg asm("lr");
	return *(linkReg);
}


