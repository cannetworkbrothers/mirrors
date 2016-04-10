/*
 * MCU_atmega8.cpp
 *
 * Created: 18.11.2015 12:46:06
 *  Author: Admin
 */ 

#include <avr/io.h>
#include "controller_atmega8.h"


char ControllerAtmega8::SpiMasterTransmit(char cData){
	/* Start transmission*/
	SPDR = cData;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))) {};
	
	return SPDR;
};
					
