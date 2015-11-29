/*
 * mcu.h
 *
 * Created: 18.11.2015 23:18:46
 *  Author: Admin
 */ 


class CanController
{
	public:
	
	CanController() {}
	virtual ~CanController() {}
	
	virtual unsigned void SPI_MasterInit(void) = 0;
	virtual unsigned char SPI_MasterTransmit(char cData) = 0;
	virtual unsigned void SPI_SlaveInit(void) = 0;
	virtual unsigned char SPI_SlaveReceive(void) = 0;
	
};