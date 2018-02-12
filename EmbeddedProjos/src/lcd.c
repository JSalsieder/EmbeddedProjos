/*
 * lcd.c
 *
 *  Created on: Dec 18, 2016
 *      Author: salsiederja
 */

#include "lcd.h"
typedef uint8_t bool;
#ifndef DELAY_H_
#include "delay.h"
#endif

void lcd_latchE(){
	//set PB2 (E) high
	*(GPIOB_BSRR) |= (1 << BSRR_S_2_BF);
	//delay to latch data
	delay(5);
	//return PB2 (E) low
	*(GPIOB_BSRR) |= (1 << BSRR_R_2_BF);
}

int lcd_isBusy(){
	int busyFlag;
	int odr_val = (*(GPIOB_ODR) & 3);
	//set PB1 high (RW)
	*(GPIOB_ODR) |= (0x1 << 1);
	//set PB0 low (RS)
	*(GPIOB_ODR) &= ~(0x1 << 0);

	//set PC11 to input mode
	//clear the BitField
	*(GPIOC_MODER) &= ~(GPIO_INPUT << MODER_11_BF);
	//set the BitField
	*(GPIOC_MODER) |= (GPIO_INPUT << MODER_11_BF);

	//save the value of the IDR
	busyFlag = (*(GPIOC_IDR) >> MODER_11_BF) & (0x1);

	//return PC11 to Output Mode
	//clear the BitField
	*(GPIOC_MODER) &= ~(GPIO_INPUT << MODER_11_BF);
	//set the BitField
	*(GPIOC_MODER) |= (GPIO_OUTPUT << MODER_11_BF);

	//return RS and RW to previous values
	*(GPIOB_ODR) &= ~(3);
	*(GPIOB_ODR) |= odr_val;

	return busyFlag;
}

void lcd_send(uint8_t command, bool r_w, bool rs ){
	//clear all dataBits to avoid stray bits
	*(GPIOC_BSRR) |= (1 << BSRR_R_11_BF);
	*(GPIOC_BSRR) |= (1 << BSRR_R_10_BF);
	*(GPIOC_BSRR) |= (1 << BSRR_R_9_BF);
	*(GPIOC_BSRR) |= (1 << BSRR_R_8_BF);
	*(GPIOB_BSRR) |= (1 << BSRR_R_1_BF);
	*(GPIOB_BSRR) |= (1 << BSRR_R_0_BF);

	//move the lower 4 bytes onto the GPIO pins Port C 11..8
	if(r_w > 0){
		//if r_w > 0 set R/W pin HIGH else set LOW
		*(GPIOB_BSRR) |= 1 << BSRR_S_1_BF;
	}else{
		*(GPIOB_BSRR) |= 1 << BSRR_R_1_BF;
	}

	if(rs > 0){
		//if rs > 0 set R/W pin HIGH else set LOW
		*(GPIOB_BSRR) |= 1 << BSRR_S_0_BF;
	}else{
		*(GPIOB_BSRR) |= 1 << BSRR_R_0_BF;
	}


	uint8_t l_nibble = (command & 0x0f);
	uint8_t u_nibble = (command >> 4);

	//clear the bits
	*(GPIOC_BSRR) |= 0xf << (8 + 16);
	//set the bits for the lower nibble
	*(GPIOC_BSRR) |= u_nibble << 8;

	while(lcd_isBusy() == true){}
	lcd_latchE();


	//clear the bits
	*(GPIOC_BSRR) |= 0xf << (8 + 16);
	//set the bits for the upper nibble
	*(GPIOC_ODR) |= l_nibble << 8;
	while(lcd_isBusy() == true){}
	lcd_latchE();
}

void lcd_command(uint8_t command){
	lcd_send(command, false, false);
}

void lcd_begin(){
	//enable the gpio ports
	*(RCC_AHB1ENR) |= (1 << GPIOAEN_BF);
	*(RCC_AHB1ENR) |= (1 << GPIOBEN_BF);
	*(RCC_AHB1ENR) |= (1 << GPIOCEN_BF);

	//set the LCD gpio's to output mode
	//clear the gpio bit fields to 0 (input);
	*(GPIOB_MODER) &= ~(0b11 << MODER_0_BF);
	*(GPIOB_MODER) &= ~(0b11 << MODER_1_BF);
	*(GPIOB_MODER) &= ~(0b11 << MODER_2_BF);
	*(GPIOC_MODER) &= ~(0b11 << MODER_8_BF);
	*(GPIOC_MODER) &= ~(0b11 << MODER_9_BF);
	*(GPIOC_MODER) &= ~(0b11 << MODER_10_BF);
	*(GPIOC_MODER) &= ~(0b11 << MODER_11_BF);
	//set the gpios to output mode
	*(GPIOB_MODER) |= (GPIO_OUTPUT << MODER_0_BF);
	*(GPIOB_MODER) |= (GPIO_OUTPUT << MODER_1_BF);
	*(GPIOB_MODER) |= (GPIO_OUTPUT << MODER_2_BF);
	*(GPIOC_MODER) |= (GPIO_OUTPUT << MODER_8_BF);
	*(GPIOC_MODER) |= (GPIO_OUTPUT << MODER_9_BF);
	*(GPIOC_MODER) |= (GPIO_OUTPUT << MODER_10_BF);
	*(GPIOC_MODER) |= (GPIO_OUTPUT << MODER_11_BF);

	//SET E LOW
	*(GPIOB_BSRR) |= (1 << BSRR_R_2_BF);
	//set RS and RW low
	*(GPIOB_BSRR) |= (1 << BSRR_R_1_BF);
	*(GPIOB_BSRR) |= (1 << BSRR_R_0_BF);
	//delay 100 ms
	delay(100);

	//set D7-D4 to 0b0011
	*(GPIOC_BSRR) |= (1 << BSRR_R_11_BF);
	*(GPIOC_BSRR) |= (1 << BSRR_R_10_BF);
	*(GPIOC_BSRR) |= (1 << BSRR_S_9_BF);
	*(GPIOC_BSRR) |= (1 << BSRR_S_8_BF);

	//Delay 30 ms
	delay(30);

	// 3 times
	for(int x = 0; x < 3; x++){
		//pulse E HIGH for 1 ms
		lcd_latchE();
		//Delay 10 ms
		delay(10);
	}

	//set D7-D4 to 0b0010
	*(GPIOC_BSRR) |= (1 << BSRR_R_8_BF);

	//pulse E HIGH for 1 ms
	lcd_latchE();

	//write 0x28 set interface to 4 bit mode, 2 lines, 5x8 font size
	lcd_command(0x28);
	//write 0x10 set cursor mode to left
	lcd_command(0x10);
	//write 0x0f set display on with the cursor on and blinking
	lcd_command(0x0f);
	//write 0x06 increment the cursor position after each write
	lcd_command(0x06);

	lcd_clear();

}

void lcd_RTL(){
	lcd_command(0x4);
}

void lcd_LTR(){
	lcd_command(0x6);
}

void lcd_noDisplay(){
	lcd_command(0x8);
}

void lcd_display(){
	lcd_command(0xC);
}

void lcd_noBlink(){
	lcd_command(0xe);
}

void lcd_blink(){
	lcd_command(0xF);
}

void lcd_noCursor(){
	lcd_command(0xC);
}

void lcd_cursor(){
	lcd_command(0xE);
}

void lcd_home(){
	lcd_command(0x2);
}

void lcd_clear(){
	lcd_command(0x1);
}

void lcd_cursorAt(int row, int col){
	int address = (col%0x40);
	if(row%2 == 1){
		address += 0x40;
	}
	lcd_command((address | 0x80));
}

void lcd_write(char ascii){
	lcd_send(ascii, false, true);
}

void lcd_print(char *string){
	char ascii = *(string);
	while(ascii != 0){
		lcd_write(ascii);
		string++;
		ascii = *(string);
	}
}





















