/*
 * MCU_atmega8.cpp
 *
 * Created: 18.11.2015 12:46:06
 *  Author: Admin
 */ 

#include <avr/io.h>
#include "controller_atmega8.h"
#include "../logger/logger.hpp"


unsigned char ControllerAtmega8::SpiMasterTransmit(unsigned char cData){
	
	CREATE_LOGGER(logger)
	LOG(logger, (char*)"atmega8.SpiTransmit started ..")
	/* Start transmission*/
	SPDR = cData;
	
	/* Wait for transmission complete */
	//while( (SPSR | (1<<SPIF) ) == 0x00) {LOG(logger, (char*)"transmitting...")};
	while(!(SPSR & (1<<SPIF)));
	
	LOG(logger, (char*) "atmega8.SpiTransmit end.")
	return SPDR;
};
					
