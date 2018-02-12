/*
 * AT28C256.c
 *
 *  Created on: Feb 11, 2017
 *      Author: salsiederja
 */
#include "AT28C256.h"

//delay for ~62.5ns per x
static void nopDelay(int x){
	for(;x > 0; x--){
		asm("nop");
	}
}

static void digitalWrite(SpinMap *p, g_eState state){
	switch (state){
	case LOW:
		Gpio_writeLow(p->port, p->pin);
		break;
	case HIGH:
		Gpio_writeHigh(p->port, p->pin);
		break;
	default:
		EXCEPTION(ERROR, "INVALID WRITE CALL [AT28C256.c : 31]");
	}
}

static void setAddressPins(const uint32_t dataAddress, SEeprom_pins* rom) {
	//put the address value on the address pins
	(dataAddress & 0x1) != 0 ?
			digitalWrite(&(rom->A0), HIGH) : digitalWrite(&(rom->A0), LOW);
	(dataAddress & 0x2) != 0 ?
			digitalWrite(&(rom->A1), HIGH) : digitalWrite(&(rom->A1), LOW);
	(dataAddress & 0x4) != 0 ?
			digitalWrite(&(rom->A2), HIGH) : digitalWrite(&(rom->A2), LOW);
	(dataAddress & 0x8) != 0 ?
			digitalWrite(&(rom->A3), HIGH) : digitalWrite(&(rom->A3), LOW);
	(dataAddress & 0x10) != 0 ?
			digitalWrite(&(rom->A4), HIGH) : digitalWrite(&(rom->A4), LOW);
	(dataAddress & 0x20) != 0 ?
			digitalWrite(&(rom->A5), HIGH) : digitalWrite(&(rom->A5), LOW);
	(dataAddress & 0x40) != 0 ?
			digitalWrite(&(rom->A6), HIGH) : digitalWrite(&(rom->A6), LOW);
	(dataAddress & 0x80) != 0 ?
			digitalWrite(&(rom->A7), HIGH) : digitalWrite(&(rom->A7), LOW);
	(dataAddress & 0x100) != 0 ?
			digitalWrite(&(rom->A8), HIGH) : digitalWrite(&(rom->A8), LOW);
	(dataAddress & 0x200) != 0 ?
			digitalWrite(&(rom->A9), HIGH) : digitalWrite(&(rom->A9), LOW);
	(dataAddress & 0x400) != 0 ?
			digitalWrite(&(rom->A10), HIGH) : digitalWrite(&(rom->A10), LOW);
	(dataAddress & 0x800) != 0 ?
			digitalWrite(&(rom->A11), HIGH) : digitalWrite(&(rom->A11), LOW);
	(dataAddress & 0x1000) != 0 ?
			digitalWrite(&(rom->A12), HIGH) : digitalWrite(&(rom->A12), LOW);
	(dataAddress & 0x2000) != 0 ?
			digitalWrite(&(rom->A13), HIGH) : digitalWrite(&(rom->A13), LOW);
	(dataAddress & 0x4000) != 0 ?
			digitalWrite(&(rom->A14), HIGH) : digitalWrite(&(rom->A14), LOW);
}

static void setIOPinMode(SEeprom_pins* rom, Mode GPIO_mode) {
	//set gpio's to INPUT
	Gpio_pinMode(rom->IO0.port, rom->IO0.pin, GPIO_mode);
	Gpio_pinMode(rom->IO1.port, rom->IO1.pin, GPIO_mode);
	Gpio_pinMode(rom->IO2.port, rom->IO2.pin, GPIO_mode);
	Gpio_pinMode(rom->IO3.port, rom->IO3.pin, GPIO_mode);
	Gpio_pinMode(rom->IO4.port, rom->IO4.pin, GPIO_mode);
	Gpio_pinMode(rom->IO5.port, rom->IO5.pin, GPIO_mode);
	Gpio_pinMode(rom->IO6.port, rom->IO6.pin, GPIO_mode);
	Gpio_pinMode(rom->IO7.port, rom->IO7.pin, GPIO_mode);
}

SEeprom_pins* ROM_init(){

//	_gpio PortA = {GPIOA};
//	_gpio PortB = {GPIOB};
//	_gpio PortC = {GPIOC};
//	_gpio PortD = {GPIOD};
//	_gpio PortH = {GPIOH};
	_gpio* Port[5] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOH};

	//CREATES THE STRUCTURE FOR THE EEPROM
	//SEeprom_pins* pROM;
	SEeprom_pins StempRom;

	SpinMap temp;
	//SETUP THE ROM STRUCTURE TO HAVE THE PORT AND PIN NUMBER FOR EACH PIN
	temp.port= Port[PB]; 	temp.pin = 5; 	StempRom.OE = temp;
	temp.port= Port[PH];	temp.pin = 1; 	StempRom.CE = temp;
	temp.port= Port[PD]; 	temp.pin = 1; 	StempRom.WE = temp;
	temp.port= Port[PC]; 	temp.pin = 0; 	StempRom.A0 = temp;
	temp.port= Port[PC];	temp.pin = 1; 	StempRom.A1 = temp;
	temp.port= Port[PC];	temp.pin = 2; 	StempRom.A2 = temp;
	temp.port= Port[PC]; 	temp.pin = 3; 	StempRom.A3 = temp;
	temp.port= Port[PC]; 	temp.pin = 4; 	StempRom.A4 = temp;
	temp.port= Port[PC]; 	temp.pin = 5; 	StempRom.A5 = temp;
	temp.port= Port[PC]; 	temp.pin = 6; 	StempRom.A6 = temp;
	temp.port= Port[PC]; 	temp.pin = 7; 	StempRom.A7 = temp;
	temp.port= Port[PC]; 	temp.pin = 8; 	StempRom.A8 = temp;
	temp.port= Port[PC]; 	temp.pin = 9; 	StempRom.A9 = temp;
	temp.port= Port[PC]; 	temp.pin = 10; 	StempRom.A10 = temp;
	temp.port= Port[PC]; 	temp.pin = 11; 	StempRom.A11 = temp;
	temp.port= Port[PC]; 	temp.pin = 12; 	StempRom.A12 = temp;
	temp.port= Port[PC]; 	temp.pin = 13; 	StempRom.A13 = temp;
	temp.port= Port[PB]; 	temp.pin = 15; 	StempRom.A14 = temp;
	temp.port= Port[PA]; 	temp.pin = 7; 	StempRom.IO0 = temp;
	temp.port= Port[PA]; 	temp.pin = 8; 	StempRom.IO1 = temp;
	temp.port= Port[PA]; 	temp.pin = 9; 	StempRom.IO2 = temp;
	temp.port= Port[PA]; 	temp.pin = 10; 	StempRom.IO3 = temp;
	temp.port= Port[PA]; 	temp.pin = 11; 	StempRom.IO4 = temp;
	temp.port= Port[PB]; 	temp.pin = 8; 	StempRom.IO5 = temp;
	temp.port= Port[PB]; 	temp.pin = 9; 	StempRom.IO6 = temp;
	temp.port= Port[PB]; 	temp.pin = 10; 	StempRom.IO7 = temp;

	//SETUP THE GPIO PORTS
	Gpio_setup(GPIOA);
	Gpio_setup(GPIOB);
	Gpio_setup(GPIOC);
	Gpio_setup(GPIOD);
	Gpio_setup(GPIOH);

	//SET THE CONTROL BITS TO 1 to do the following:
	//	DESELECT THE CHIP <-- CE = 1
	//	DISABLE OUTPUT	<-- OE = 1
	//  DISABLE WRITE MODE <-- WE = 1
	digitalWrite(&(StempRom.WE), HIGH);
	digitalWrite(&(StempRom.OE), HIGH);
	digitalWrite(&(StempRom.CE), HIGH);

	SEeprom_pins *heapROM;
	heapROM = (SEeprom_pins*)calloc(1, sizeof(StempRom));
	if(heapROM == 0){
		EXCEPTION(FATAL_ERROR, "EEPROM INITILIZATION FAILURE [AT28256.c : 107]");
	}
	uint32_t *put = (uint32_t*)heapROM;
	uint32_t *get = (uint32_t*)&StempRom;

	for(int x = 0; x < sizeof(SEeprom_pins); x++){
		*(put+x) = *(get+x);
	}







	return heapROM;
}

void ROM_write(SEeprom_pins* rom, const uint32_t dataAddress, const uint8_t dataByte){

	//verify the address is valid, between 0x0 and 0x7FFF
	if(dataAddress > ROM_MAX_ADDRESS){
		EXCEPTION(ERROR, "INVALID WRITE ADDRESS: DATA NOT WRITTEN [AT28C256.c : 105]");
		return;
	}
	//set GPIO pins to output
	setIOPinMode(rom, Output);

	//set OE<-LOW, WE<-HIGH, CE<-LOW
	digitalWrite(&(rom->OE), LOW);
	digitalWrite(&(rom->WE), HIGH);
	digitalWrite(&(rom->CE), LOW); //enables the chip (now draws more power from the supply)

	//put the address value on the address pins
	setAddressPins(dataAddress, rom);
	//set the data bits to their proper values
	(dataByte & 0x1) != 0 ? digitalWrite(&(rom->IO0), HIGH) : digitalWrite(&(rom->IO0), LOW);
	(dataByte & 0x2) != 0 ? digitalWrite(&(rom->IO1), HIGH) : digitalWrite(&(rom->IO1), LOW);
	(dataByte & 0x4) != 0 ? digitalWrite(&(rom->IO2), HIGH) : digitalWrite(&(rom->IO2), LOW);
	(dataByte & 0x8) != 0 ? digitalWrite(&(rom->IO3), HIGH) : digitalWrite(&(rom->IO3), LOW);
	(dataByte & 0x10) != 0 ? digitalWrite(&(rom->IO4), HIGH) : digitalWrite(&(rom->IO4), LOW);
	(dataByte & 0x20) != 0 ? digitalWrite(&(rom->IO5), HIGH) : digitalWrite(&(rom->IO5), LOW);
	(dataByte & 0x40) != 0 ? digitalWrite(&(rom->IO6), HIGH) : digitalWrite(&(rom->IO6), LOW);
	(dataByte & 0x80) != 0 ? digitalWrite(&(rom->IO7), HIGH) : digitalWrite(&(rom->IO7), LOW);

	//OE LOW to prepare to write
	digitalWrite(&(rom->WE), HIGH);

	//delay >10ns for Address setup, data setup, and OE setup time
	nopDelay(1); //~62 ns

	//Pull WE low to begin writing to the ROM
	digitalWrite(&(rom->WE), LOW);

	//delay >100ns to store data
	nopDelay(3); // ~187ns

	//Pull WE high to end write cycle
	digitalWrite(&(rom->WE), HIGH);

	//Pull OE HIGH to disable output
	digitalWrite(&(rom->OE), LOW);

	//Pull CE HIGH to disable chip (goes into LOW POWER STATE)
	digitalWrite(&(rom->CE), HIGH);

}

uint8_t ROM_read(SEeprom_pins *rom, const uint32_t dataAddress){

	//verify the address is valid, between 0x0 and 0x7FFF
	if(dataAddress > ROM_MAX_ADDRESS){
		EXCEPTION(ERROR, "INVALID READ ADDRESS: NULL RETURNED [AT28C256.c : 202]");
		return 0;
	}

	//keep WE HIGH so nothing is written
	digitalWrite(&(rom->WE), HIGH);

	setAddressPins(dataAddress, rom);

	//pull CE LOW  (data valid after 150ns)
	digitalWrite(&(rom->CE), LOW); //enables the chip (now draws more power from the supply)

	//set gpio's to INPUT
	setIOPinMode(rom, Input);

	uint8_t retRead = 0;

	//read in the data bits
	retRead |= (Gpio_digitalRead(rom->IO0.port, rom->IO0.pin) << 0);
	retRead |= (Gpio_digitalRead(rom->IO1.port, rom->IO1.pin) << 1);
	retRead |= (Gpio_digitalRead(rom->IO2.port, rom->IO2.pin) << 2);
	retRead |= (Gpio_digitalRead(rom->IO3.port, rom->IO3.pin) << 3);
	retRead |= (Gpio_digitalRead(rom->IO4.port, rom->IO4.pin) << 4);
	retRead |= (Gpio_digitalRead(rom->IO5.port, rom->IO5.pin) << 5);
	retRead |= (Gpio_digitalRead(rom->IO6.port, rom->IO6.pin) << 6);
	retRead |= (Gpio_digitalRead(rom->IO7.port, rom->IO7.pin) << 7);

	return retRead;
}
