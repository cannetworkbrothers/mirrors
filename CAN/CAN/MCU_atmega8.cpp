/*
 * MCU_atmega8.cpp
 *
 * Created: 18.11.2015 12:46:06
 *  Author: Admin
 */ 


#include "MCU_atmega8.h"


<<<<<<< HEAD:CAN/CAN/MCU_atmega8.cpp
unsigned char mcu_atmega8::SPI_MasterTransmit(char cData)
=======
void SPI_MasterTransmit(char cData)
>>>>>>> parent of b24555f... without 2 error:CAN/MCU_atmega8.cpp
{
	/* Запуск передачи данных */
	SPDR = cData;
	/* Ожидание завершения передачи данных */
	while(!(SPSR & (1<<SPIF))) {};
		
};
