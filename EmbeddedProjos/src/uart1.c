/*
 * uart1.c
 *
 *  Created on: Feb 12, 2017
 *      Author: salsiederja
 */

#include "uart1.h"
#define USART1_RX_PIN  7
#define USART1_TX_PIN  6


static _gpio port = {GPIOB};


void init_usart1(){
	// Enable clocks for GPIOA and USART2
	(*RCC_APB2ENR) |= (1 << USART1EN_BF);
	Gpio_setup(&port);

	Gpio_AlternateFunction(&port, USART1_RX_PIN, AF7);
	Gpio_AlternateFunction(&port, USART1_TX_PIN, AF7);

	/*
	 * Setup of the usart
	 * CR1 //
	 * UE <- 1
	 * M <- 0 //8 data bits 1 start bit
	 * PCE <- 0 //No Parity
	 * PXIE <- 0
	 * TX <- 1 //Enable Transmit
	 * RX <- 0 //Disable Receive
	 * SBK <- 0 // Break starts off
	 *
	 * CR2 //
	 * LINEN <- 1// LINE mode enabled to send line breaks
	 * STOP <- 0x2 // 2 stop bits
	 * DMAT <- 1 // enable DMA access for the transmitter;
	 *
	 * BRR <- 4 << 4 = 250Kbtis/s
	 *
	 */
	(*USART1_CR1) &= 0xFFFF4000; //set all to 0;
	(*USART1_CR1) |=  ((1 << UE_BF) | (1 << TE_BF));

	(*USART1_CR2) &= 0xFFFF8090; //set all to 0;
	(*USART1_CR2) |= (0x2 << STOP_BF);

	(*USART1_CR3) &= 0xFFFFF000; //seta all to 0;
	//(*USART1_CR3) |= (1 << DMAT_BF);

	(*USART1_BRR) &= 0xFFFF0000;
	(*USART1_BRR) |= (4 << 4);
}

void usart1_write(uint8_t data){
	while(((*USART1_SR) & (1<<TXE_BF)) == 0){
		asm("nop");
	}
	(*USART1_DR) |= data;
}


