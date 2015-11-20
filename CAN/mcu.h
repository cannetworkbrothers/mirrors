/*
 * mcu.h
 *
 * Created: 18.11.2015 23:18:46
 *  Author: Admin
 */ 


#ifndef MCU_H_
#define MCU_H_


class mcu
{
	public:
	
	virtual void SPI_MasterTransmit(char cData) = 0;
	
	
	};


#endif /* MCU_H_ */