/*
 * MCU_atmega8.cpp
 *
 * Created: 18.11.2015 12:46:06
 *  Author: Admin
 */ 


#include "controller_atmega8.h"
//#include "avr/iom8a.h" // here include atmega8 header 


unsigned char ControllerAtmega8::SPI_MasterTransmit(char cData){
	/* Start transmission*/
	SPDR = cData;
	
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF))) {};		
};

unsigned char ControllerAtmega8::SPI_SlaveReceive(){
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	
	/* Return data register */
	return SPDR;
};