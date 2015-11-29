/*
 * MCU_atmega8.h
 *
 * Created: 18.11.2015 12:30:26
 *  Author: Admin
 */ 


#include <avr/io.h>
#include "controller/can_controller.h"

class ControllerAtmega8:public CanController
{
	private:
	
	public:
	
	unsigned void SPI_MasterInit(void);
	unsigned char SPI_MasterTransmit(char cData);
	unsigned void SPI_SlaveInit(void);
	unsigned char SPI_SlaveReceive(void);
		
	};




#endif /* MCU_ATMEGA8_H_ */