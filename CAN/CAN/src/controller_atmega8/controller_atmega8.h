/*
 * MCU_atmega8.h
 *
 * Created: 18.11.2015 12:30:26
 *  Author: Admin
 */ 


#include "../controller/controller.h"
#include "avr/interrupt.h"


class ControllerAtmega8 : public Controller
{	
	public:
	
	ControllerAtmega8() {
		
		// set SPI
		
		SPCR |= (1<<SPE);   // enable SPI
		SPSR = (0<<SPI2X);  // pres caller
		SPCR = (0<<SPR1)|(0<<SPR0);         // fspi=fosc/2
		SPCR |= (1<<DORD);   // receive from low rate 
		SPCR |=(1<<MSTR);  // mode MASTER
		DDRB |= (1<<DDB2);  // port B2 this is a SS pin. For Master mode this must be OUT
		SPCR |= (1<< CPOL)|(1<<CPHA); // synchronization begin Leading Edge, sample data beginning Trailing Edge Mode 3 (1:1)
		SPCR |=(1<<SPIE); // enable interrupt SPI
	    sei();   // global interrupt Enable
		
		
		};
	~ControllerAtmega8() {};
	
	unsigned char SpiMasterTransmit(unsigned char cData);	
};