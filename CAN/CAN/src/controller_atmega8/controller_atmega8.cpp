/*
 * MCU_atmega8.cpp
 *
 * Created: 18.11.2015 12:46:06
 *  Author: Admin
 */ 

#include <avr/io.h>
#include "controller_atmega8.h"


unsigned char ControllerAtmega8::SPI_MasterTransmit(char cData){
	/* Start transmission*/
	SPDR = cData;														// spi data register
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))) {};										// spi status register
};