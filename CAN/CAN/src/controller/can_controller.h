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
	
	virtual void SPI_MasterInit() = 0;
	virtual unsigned char SPI_MasterTransmit(char cData) = 0;
	virtual void SPI_SlaveInit() = 0;
	virtual unsigned char SPI_SlaveReceive() = 0;
	
};