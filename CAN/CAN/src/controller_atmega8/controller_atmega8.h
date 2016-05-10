/*
 * MCU_atmega8.h
 *
 * Created: 18.11.2015 12:30:26
 *  Author: Admin
 */ 


#include "../controller/controller.h"
#include "../logger/logger.hpp"
#include "avr/interrupt.h"


class ControllerAtmega8 : public Controller
{	
	public:
	
	ControllerAtmega8() {
		
		// set SPI
		
		DDRB |= (1<<DDB2);  // port B2 - SS pin. For Master mode this must be OUT
		DDRB |= (1<<DDB3);  // port B3 - MOSI pin. For Master mode this must be OUT
		DDRB &= ~(1<<DDB4); // port B4 - MISO pin. For Master mode this must be IN
		DDRB |= (1<<DDB5);  // port B5 - SCK pin. For Master mode this must be OUT
		
		//PORTB |= (1<<DDB2)|(1<<DDB3)|(1<<DDB4)|(1<<DDB5);
		
		SPCR = (1<<SPE) | (1<<MSTR);  // mode MASTER
		SPSR = (1<<SPI2X);
		
		//SPSR |= (1<<SPI2X);  // pres caller
		//SPCR |= (1<<SPR1);
		//SPCR |= (1<<SPR0); // fspi=fosc/128
		//SPCR |= (1<<DORD); // receive from low rate 
		//SPCR |= (1<<CPOL); // synchronization begin Leading Edge Mode 3
		//SPCR |= (1<<CPHA); // sample data beginning Trailing Edge Mode 3
		//SPCR |= (1<<SPIE); // enable interrupt SPI
		//SPCR |= (1<<SPE);   // enable SPI
	    //sei();   // global interrupt Enable
		};
	~ControllerAtmega8() {};
	
	unsigned char SpiMasterTransmit(unsigned char cData);	
};