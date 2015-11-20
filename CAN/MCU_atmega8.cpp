/*
 * MCU_atmega8.cpp
 *
 * Created: 18.11.2015 12:46:06
 *  Author: Admin
 */ 


#include "MCU_atmega8.h"


void mcu_atmega8::SPI_MasterTransmit(char cData)
{
	/* Запуск передачи данных */
	SPDR = cData;
	/* Ожидание завершения передачи данных */
	while(!(SPSR & (1<<SPIF))) {};
		
}
