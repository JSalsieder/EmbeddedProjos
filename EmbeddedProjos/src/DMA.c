/*
 * DMA.c
 *
 *  Created on: Feb 14, 2017
 *      Author: salsiederja
 */
#include "DMA.h"



typedef volatile uint32_t* _register;

typedef struct{
	_register ICTR;
	_register STIR;
	_register ISERx;
	_register ICERx;
	_register ISPRx;
	_register ICPRx;
	_register IPRx;
}NVIC;

#define NVIC_DMA2_S7_IRQ 6

typedef struct{
	_register HISR;
	_register HIFCR;
	_register S7CR;
	_register S7NDTR;
	_register S7PAR;
	_register S7M0AR;
	_register S7M1AR;
	_register S7FRC;
} DMA;

DMA DMA2 = {
		(uint32_t*) 0x40026404,
		(uint32_t*) 0x4002640C,
		(uint32_t*) 0x400264B8,
		(uint32_t*) 0x400264BC,
		(uint32_t*) 0x400264C0,
		(uint32_t*) 0x400264C4,
		(uint32_t*) 0x400264C8,
		(uint32_t*) 0x400264CC
};

NVIC NVIC2 = {
		(uint32_t*) 0xE000E004,
		(uint32_t*) 0xE000EF00,
		(uint32_t*) 0xE000E108,
		(uint32_t*) 0xE000E188,
		(uint32_t*) 0xE000E208,
		(uint32_t*) 0xE000E288,
		(uint32_t*) 0x0
};

static uint32_t bytes = 0;

void DMA_init(uint8_t* start_address, uint32_t numberOfBytes){
	bytes = numberOfBytes;
	(*GPIOB_OSPEEDR) |= (0b11 << 12);
	(*NVIC2.ISERx) |= 1 << NVIC_DMA2_S7_IRQ; //enable the DMA interrupts
	(*RCC_AHB1ENR) |= 1 << 22;	// Enable DMA2 Clock
	(*USART1_CR3) |= 1 << DMAT_BF; //enable DMA for USART1
	(*DMA2.S7CR) &= 0; 			//  Clear control register

	(*DMA2.S7PAR) |= (uint32_t)USART1_DR;		// location where data is written to USART1_DataRegister
	(*DMA2.S7M0AR)|= (uint32_t)start_address; // start address of data

	(*DMA2.S7CR) |= (4 << 25); 	// set Channel to 4 (USART1_TX)
	(*DMA2.S7CR) |= (3 << 16); 	// Priority level Very High
	(*DMA2.S7CR) |= (1 << 10); 	// Memory increment mode enabled
	(*DMA2.S7CR) |= (1 << 6);	// Direction is Memory -> peripheral
	(*DMA2.S7CR) |= (1 << 4); 	//Transfer Complete Interrupt Enabled

	(*DMA2.S7FRC) |= (1 << 2); // Direct mode off;
	(*DMA2.S7FRC) |= (0b11); //use full FIFO QUEUE

	//
	DMA2_Stream7_IRQHandler();

}

void DMA2_Stream7_IRQHandler(){
	/*
	 * This function creates the Break = 176us TYP , MAB = 12uS TYP, and then starts the data transmission
	 * ------________-------_[0..7]--_[0..7]--_ ~~~~_[0..7]---------------
	 * IDLE    BREAK   MAB  S scode sS data1 sS     S data512 s IDLE
	 */

	//clear interrupt flag
	(*DMA2.HIFCR) |= ( 0xf << 24 | 0x1 << 22);
	(*NVIC2.ICERx) |= (1 << NVIC_DMA2_S7_IRQ);

	(*DMA2.S7NDTR)|= bytes;	// set the number of bytes in the number-of-data register
	(*USART1_SR) &= ~(1 << TC_BF); // Clear Transmission Complete in USART bit

	asm("CPSID i"); //disable interrupts due to the time sensitive nature of this function

	//*******IDLE*******
	for(int t = 244; t > 0; t--){
		//hold Idle for 200us
		asm("nop");
	}
	//******************

	//*******BREAK*******
	(*GPIOB_MODER) &= ~(0b11 << 12);
	(*GPIOB_MODER) |= (0b01 << 12);
	(*USART1_CR1) &= ~(1 << TE_BF); // disable USART transmitter to pull line low
	for(int t = 216; t > 0; t--){
		//Break for  176us
		asm("nop");
	}
	(*GPIOB_MODER) &= ~(0b11 << 12);
	(*GPIOB_MODER) |= (0b10 << 12);
	//*******************

	//*******MAB*******
	(*USART1_CR1) |= (1 << TE_BF); // Enable USART transmitter to pull line High
	//for(int t = 1; t > 0; t--){
		//Mark for 11.875us
	//	asm("nop");
	//}
	//*******************

	asm("CPSIE i"); //allow interupts again;
	(*DMA2.S7CR) |= 1; //Enable the stream ****TRANSMISSION BEGINS****

	(*NVIC2.ISERx) |= (1 << NVIC_DMA2_S7_IRQ);
}

