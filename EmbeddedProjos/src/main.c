/*
 * main.c
 *
 *  Created on: Feb 3, 2016
 *      Author: JOHN Salsieder
 *
 *
 *	purpose of the lab:
 *		Provide a DMX controller for use with any DMX network. granting the user 1 Universe
 *		of channels to control in a 1:1 patch.
 *
 *
 *	Background on DMX:
 *			DMX or DMX512 is used as a control network for theatrical application
 *		where signal failure will not compromise safety. Primarily this Protocol is
 *		used to control lighting fixtures.
 *		Each DMX bus is known as a Universe, each Universe has 512 channels hence, DMX512.
 *			A lighting fixture connected to the DMX bus is assigned an address which corresponds to a
 *		starting channel and then uses X number of channels as control signals. Dimmer's often are a
 *		single channel device as each dimmer controls the power going to a single fixture. an RGB LED fixture
 *		on the other hand may have 3 channels, one for each color.
 *			Standard DMX consoles interface with the user using channels and address which are patched to each other
 *		(like a digital switchboard) so a user may patch channel 1 to address 12 and address 13 this  means entering
 *		a command as such "channel 1 @ 50%" will send a signal of 50% to both address 12 and address 13. The simplest
 *		patch is a 1:1 patch where each channel has the same number as the address it is patched to and is only patched
 *		to that one address.
 *
 *
 *	Peripherals used in this lab: (*) = new peripheral usage
 *
 *		internal:
 *			1) *USART1		--  Writes DMX signal to the transceiver IC
 *			2) USART2		-- 	Writes to Serial Console for Debug
 *			3) GPIO			--	Interfaces all external peripherals
 *			4) *DMA2		-- 	Generate non-interruptible data stream independent of the CPU
 *			5) NVIC			--  Handles Interrupts with Priority Control
 *			6) *EXTI		--  Handles External Interrupts (encoder)
 *
 *		external:
 *			7) LCD						-- GUI
 *			8) KEYPAD					-- UI (polling)
 *			9) *ROTARY ENCODER			-- UI (Interrupt Driven)
 *			10) *DS75176B Transceiver	-- Creates differential output line  [data in] --> [D+ out] and [D- out]
 *
 *
 *	Things I could have done better for this lab:
 *
 *      1)	The LCD is slowing down my Encoder interrupts and causing the encoder to
 *      	drop entries. I would fix this by creating a FIFO buffer of function pointers
 *      	where each pointer is a lcd command. the buffer is emptied 1 command at a time
 *      	whenever the LCD.busyFlag is empty. because there is no interrupt directly connected to the
 *      	lcd would need a timer (systick) to count down any create an interrupt every few milliseconds.
 *      	this would be a low priority interrupt so it would not interfere with either the DMA reset or Encoder reads.
 *
 *		2)	I would have added the functionality for the eeprom and additional states for creating a show mode
 *			with saved presets, able to be executed sequentially or by user input to goto an out-of-sequence preset
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <inttypes.h>
#include "DMA.h"
#include "uart_driver.h"
#include "uart1.h"
#include "DS75176B.h"
#include "encoder.h"
#include "delay.h"
#include "Gpio.h"
#include "keypad.h"
#include "Timers.h"
#include "lcd.h"

#define NUMBER_OF_STATES 5
#define NUMBER_OF_KEYSETS 7

#define Pfail lcd_clear(); lcd_print("Function not"); lcd_cursorAt(1,0); lcd_print("implemented yet");
#define Pchannel lcd_print("CH "); lcd_blink();
#define Penter lcd_print(" *");
#define Pat lcd_print("@ ");
#define Precord lcd_print("REC ");
#define Pque lcd_print("QUE ");
#define Pnext lcd_print("NEXT ");
#define	Pnewline lcd_clear(); lcd_print("DMX-512  CONTROL"); lcd_cursorAt(1,0);

#define F_CPU 16000000UL

typedef void(*functPtr)();
typedef enum {DIGIT, CLR = 0xa, AT = 0xb, CH = 0xc, REC = 0xd , GO = 0xe, ENTER = 0xf} KEY;
typedef enum {HOME, CHANNEL, VALUE, HOLD, FAIL} state;
typedef uint16_t channel;
typedef uint8_t dmxVal;

typedef struct {
	uint8_t start_code;
	dmxVal data[512];
}Universe;

typedef struct {
	state nextState;
	functPtr task; 
}transition;

Universe *DMX;


static uint8_t mutated = 0;
static volatile int encoder_value;
static volatile channel captured_channel = 0;
static volatile dmxVal captured_channel_value= 0;
static volatile int key = 0;

//prototypes

void requestAndMapCurrentValue();

void mapAndStoreNewValue();

void printValue();
//print CH to LCD
void UI_channel();

void ENC_rot_ISR();

void UI_fail();

void UI_main();

void release_captured_channel();

//also enable the encoder
void get_captured_channel_value();

//update the static value and send to the display
//does not latch value
void alterValue();

//update the static value and send to the display
//!LATCH VALUE
void clearValue();

//!LATCH VALUE
void latch_current_value_gotoHOLD();

//!LATCH VALUE
void latch_current_value_gotoCHANNEL();

//literally nothing
void doNothing();

//modify the selected channel number
void alterChannel();



/*
 * transition table 
*/
transition functionTable[NUMBER_OF_STATES][NUMBER_OF_KEYSETS] = {
/* Current state */
		/*1DIGIT*/		//
		/*2CLR*/		//
		/*3AT*/			//
		/*4CH*/			// <- KeyGroup pressed
		/*5REC*/		//
		/*6GO*/			//
		/*7ENTER*/		//

/*HOME*/
		{{HOME, doNothing},
		{HOME, doNothing},
		{HOME, doNothing},
		{CHANNEL, UI_channel},
		{FAIL, UI_fail},
		{HOME, doNothing},
		{HOME, doNothing}},

/*CHANNEL*/
		{{CHANNEL, alterChannel},
		{CHANNEL, release_captured_channel},
		{VALUE, get_captured_channel_value},
		{CHANNEL, doNothing},
		{FAIL, UI_fail},
		{CHANNEL, doNothing},
		{CHANNEL, doNothing}},

/*VALUE*/
		{{VALUE, alterValue},
		{VALUE, clearValue},
		{VALUE, doNothing},
		{CHANNEL, latch_current_value_gotoCHANNEL},
		{FAIL, UI_fail},
		{VALUE, doNothing},
		{HOLD, latch_current_value_gotoHOLD}},


/*HOLD*/
		{{HOLD, doNothing},
		{HOME, UI_main},
		{HOLD, doNothing},
		{CHANNEL, UI_channel},
		{FAIL, UI_fail},
		{HOLD, doNothing},
		{HOLD, doNothing}},

/*FAIL*/
		{{HOME, UI_main},
		{HOME, UI_main},
		{HOME, UI_main},
		{CHANNEL, UI_channel},
		{FAIL, doNothing},
		{HOME, UI_main},
		{HOME, UI_main}},

		
};


//Functions for transition table

//print CH to LCD
void UI_channel(){
	Encoder_noInterrupts();
	captured_channel = 0;
	Pnewline Pchannel
}

void UI_fail(){
	Encoder_noInterrupts();
	lcd_noCursor();
	Pfail
}

void UI_main(){
	Encoder_noInterrupts();
	Pnewline
}

void release_captured_channel(){\
	captured_channel = 0;
	lcd_cursorAt(1, 3);
	lcd_print("    ");
	lcd_cursorAt(1, 3);
}

//also enable the encoder
void get_captured_channel_value(){
	mutated = 0;
	requestAndMapCurrentValue();
	lcd_cursorAt(1,7);
	Pat
	printValue();
	lcd_cursorAt(1, 9);
	//captured_channel_value = 0;
	Encoder_Interrupts(ENC_rot_ISR);
}

//update the static value and send to the display
//does not latch value
void alterValue(){
	if(mutated == 0){
		captured_channel_value = 0;
		mutated = 1;
	}
	captured_channel_value *= 10;
	captured_channel_value += key;
	if(captured_channel_value > 100){captured_channel_value = 100;}
	if(captured_channel_value < 0){captured_channel_value = 0;}
	printValue();
}

//update the static value and send to the display
//!LATCH VALUE
void clearValue(){
	captured_channel_value = 0;
	printValue();
}

//!LATCH VALUE
void latch_current_value_gotoHOLD(){
	Encoder_noInterrupts();
	mapAndStoreNewValue();
	Penter
	lcd_noCursor();
}

//!LATCH VALUE
void latch_current_value_gotoCHANNEL(){
	mapAndStoreNewValue();
	captured_channel = 0;
	UI_channel();
}

//literally nothing
void doNothing(){asm("nop");}

//modify the selected channel number
void alterChannel(){
	char str[4];
	captured_channel *= 10;
	captured_channel += key;
	if(captured_channel > 512){captured_channel = 512;}
	if(captured_channel < 1){captured_channel = 1;}
	lcd_cursorAt(1, 3);
	lcd_print("    ");
	lcd_cursorAt(1, 3);
	sprintf(str, "%d", captured_channel);
	lcd_print(str);
}


// main
int main(void){

	// initialize the LCD and print a startup message
	lcd_begin();
	lcd_print("Initializing");
	lcd_noCursor();

	//create an instruction buffer for the LCD
	functPtr *buffer = calloc(1, sizeof(functPtr));
	if(buffer == 0){
		EXCEPTION(FATAL_ERROR, "COULD NOT ALLOCATE MEMORY: [main.c : 322]");
	}

	//timer setup


	//set start state
	state current_state = HOME;
	mutated = 0;

	//initialize usart_2 for debugging
	init_usart2(19200,F_CPU);

	//initialize the encoder and set the current value to wherever the knob is
	Encoder_init();
	encoder_value = Encoder_get_value();

	//initialize the uart1 for DMX transmission
	init_usart1();

	//set the starting values of the captured channel
	captured_channel = 0;
	captured_channel_value = 0;

	//allocate memory for the DMX universe, define the start code to null
	DMX = calloc(1, sizeof(Universe));
	if(DMX == 0){
		EXCEPTION(FATAL_ERROR, "COULD NOT ALLOCATE MEMORY: [main.c : 346]");
	}
	DMX->start_code = 0; //USITT Default null start code for dimmers as per DMX512 & DMX512/1990 standards

	//initialize the DMA
	DMA_init((uint8_t*)DMX, (uint32_t)sizeof(Universe));

	//Initialize the keypad
	kpad_begin();

	//Initialize the Transciver_IC;
	DS75176B* RxTx = Transciever_init();
	Transciever_Output(RxTx);

	//print a message indicating the program is ready for user input
	lcd_clear();
	Pnewline

	//Start of State Machine
	for(;;){
		//wait for key press and store the key that is pressed
		//into a global variable for use with the other functions
		key = kpad_poll();
		KEY keygroup;
		//map key pressed to either digits or one of the ENUM keys
		switch (key){
		case CLR: keygroup = 1; break;
		case AT: keygroup = 2; break;
		case CH: keygroup = 3; break;
		case REC: keygroup = 4; break;
		case GO: keygroup = 5; break;
		case ENTER: keygroup = 6; break;
		default: keygroup = DIGIT;
		}

		//do the task (call the function) at this table location
		functionTable[current_state][keygroup].task();
		//proceed to next state
		current_state = functionTable[current_state][keygroup].nextState;

		while( kpad_read() != -1){} // wait for key to be released
	}
}

typedef enum {CLW=1, CCLW=-1, STAT=0} encoderstate;

// new state =[current state] [last state]
encoderstate enc_trantbl[4][4]= {
/* current = 0*/		{STAT, CLW, STAT, CCLW},
/* current = 1*/		{CCLW, STAT, CLW, STAT},
/* current = 2*/		{STAT, CCLW, STAT, CLW},
/* current = 3*/		{CLW, STAT, CCLW, STAT},
};

void ENC_rot_ISR(){
	// ROTATION PATTERN
	//2 3 0 1 2
	//>> CW >>

	requestAndMapCurrentValue();
	int current_value = Encoder_get_value();
	switch(current_value){
	case 0:
		if(encoder_value == 3){ captured_channel_value+=3; }
		if(encoder_value == 1){ captured_channel_value--; }
		break;
	case 1:
		if(encoder_value == 0){ captured_channel_value+=3; }
		if(encoder_value == 2){ captured_channel_value--; }
		break;
	case 2:
		if(encoder_value == 1){ captured_channel_value+=3; }
		if(encoder_value == 3){ captured_channel_value--; }
		break;
	case 3:
		if(encoder_value == 2){ captured_channel_value+=3; }
		if(encoder_value == 0){ captured_channel_value--; }
		break;
	}
	encoder_value = current_value;
	printValue();
	mapAndStoreNewValue();
}


void printValue(){
	//mapAndStoreNewValue();
	if(captured_channel_value > 200){
		captured_channel_value = 0;
	}
	if(captured_channel_value > 100){
		captured_channel_value = 100;
	}
	char str[4];
	lcd_cursorAt(1, 9);
	lcd_print("   ");
	lcd_cursorAt(1, 9);
	if(captured_channel_value > 99){
		lcd_print("FL");
		return;
	}
	sprintf(str, "%d%%", captured_channel_value);
	lcd_print(str);
}

void mapAndStoreNewValue(){

	if(captured_channel_value > 200){
			captured_channel_value = 0;
		}
		if(captured_channel_value > 100){
			captured_channel_value = 100;
		}
	//TODO: map 0-100 to 0-255 and write memory;
	if(captured_channel_value == 100){
		DMX->data[captured_channel-1] = 255;
	}else{
		DMX->data[captured_channel-1] = (dmxVal)(captured_channel_value * 2.55);
	}
}

void requestAndMapCurrentValue(){
	captured_channel_value = (dmxVal)(DMX->data[captured_channel-1] / 2.55);
}







