/*
 * MCU_atmega8.h
 *
 * Created: 18.11.2015 12:30:26
 *  Author: Admin
 */ 


#ifndef MCU_ATMEGA8_H_
#define MCU_ATMEGA8_H_

#include <avr/io.h>
#include "mcu.h"

class mcu_atmega8:public mcu
{
	private:
	
	public:
	
	void SPI_MasterTransmit(char cData);
		
	};




#endif /* MCU_ATMEGA8_H_ */